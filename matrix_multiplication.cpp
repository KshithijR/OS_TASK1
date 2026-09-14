#include <pthread.h>
#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
static const int SIZE = 100;
static const size_t THREAD_STACK_SIZE = 256 * 1024;

static int A[SIZE][SIZE];
static int B[SIZE][SIZE];
static int C[SIZE][SIZE];

std::atomic<long> done_count(0);

struct ThreadData {
    int row;
    int col;
};
void* multiplyOneElement(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    int row = data->row;
    int col = data->col;
    delete data;

    int total = 0;
    for (int k = 0; k < SIZE; ++k) {
        total += A[row][k] * B[k][col];
    }
    C[row][col] = total;

    done_count.fetch_add(1, std::memory_order_relaxed);
    return nullptr;
}

void* printProgress(void*) {
    long total = static_cast<long>(SIZE) * static_cast<long>(SIZE);
    int lastPercent = -1;

    while (done_count.load(std::memory_order_relaxed) < total) {
        long current = done_count.load(std::memory_order_relaxed);
        int percent = static_cast<int>((current * 100) / total);
        if (percent != lastPercent) {
            int filled = percent / 10;
            printf("\r[");
            for (int i = 0; i < 10; ++i) printf(i < filled ? "#" : ".");
            printf("] %3d%%", percent);
            fflush(stdout);
            lastPercent = percent;
        }
        usleep(20000);
    }
    printf("\r[##########] 100%%\n");
    fflush(stdout);
    return nullptr;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    printf("Creating %d x %d matrices...\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }

    long totalThreads = static_cast<long>(SIZE) * static_cast<long>(SIZE);
    printf("Spawning one thread per output element (%ld threads total)...\n", totalThreads);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);

    pthread_t* threads = new pthread_t[totalThreads];

    pthread_t progressThread;
    pthread_create(&progressThread, nullptr, printProgress, nullptr);

    printf("\nMatrix multiplication started...\n\n");

    long idx = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[idx], &attr, multiplyOneElement, data);
            ++idx;
        }
    }

    for (long t = 0; t < totalThreads; ++t) {
        pthread_join(threads[t], nullptr);
    }
    pthread_join(progressThread, nullptr);

    pthread_attr_destroy(&attr);
    delete[] threads;

    printf("\nAll threads finished.\n\n");

    auto print5x5 = [](const char* name, int mat[SIZE][SIZE]) {
        printf("%s (top-left 5x5):\n", name);
        for (int i = 0; i < 5; ++i) {
            printf("[");
            for (int j = 0; j < 5; ++j) {
                printf("%d%s", mat[i][j], j < 4 ? ", " : "");
            }
            printf("]\n");
        }
        printf("\n");
    };
    print5x5("A", A);
    print5x5("B", B);
    print5x5("C", C);

    int check00 = 0;
    for (int k = 0; k < SIZE; ++k) check00 += A[0][k] * B[k][0];

    int checkLast = 0;
    for (int k = 0; k < SIZE; ++k) checkLast += A[SIZE - 1][k] * B[k][SIZE - 1];

    printf("Thread result C[0][0]         = %d\n", C[0][0]);
    printf("Normal result check           = %d\n", check00);
    printf("Thread result C[%d][%d]     = %d\n", SIZE - 1, SIZE - 1, C[SIZE - 1][SIZE - 1]);
    printf("Normal result check           = %d\n", checkLast);

    bool match = (C[0][0] == check00) && (C[SIZE - 1][SIZE - 1] == checkLast);
    printf("Result: %s\n", match ? "MATCH" : "MISMATCH");

    return match ? 0 : 1;
}