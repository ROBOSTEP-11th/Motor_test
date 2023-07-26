// モーターを動作確認するためのコード
#include "mbed.h"
#include "NsPwmOut.h"

// duty比
const float rotS = 0.2; // 0.1, 0.15, 0.3, 0.5, 0.8
const uint32_t sleep_time_ms = 2500;

using namespace mext;

NsPwmOut pin1A(PA_3);
NsPwmOut pin1B(PA_1);

UnbufferedSerial ser(CONSOLE_TX, CONSOLE_RX);

void wait_for_key(char k);

int main() {
    pin1A.period_us(50);
    pin1B.period_us(50);

    // スペースを押すと始まる
    printf("press space to start.\n");
    wait_for_key(' ');
    printf("\n");

    // モーターが正転逆転を繰り返す
    while (true) {
        pin1A = rotS;
        pin1B = 0;
        printf("rotA\n");
        thread_sleep_for(sleep_time_ms);

        pin1A = 0;
        pin1B = 0;
        printf("SL\n");
        thread_sleep_for(sleep_time_ms);

        pin1A = 0;
        pin1B = rotS;
        printf("rotB\n");
        thread_sleep_for(sleep_time_ms);
        
        pin1A = 0;
        pin1B = 0;
        printf("SL\n");
        thread_sleep_for(sleep_time_ms);
    }
}

// 指定された文字が入力されるまで待つ関数
void wait_for_key(char k) {
    while (true) {
        char c;
        ser.read(&c, 1);
        if (c == k) {
            break;
        }
    }
}