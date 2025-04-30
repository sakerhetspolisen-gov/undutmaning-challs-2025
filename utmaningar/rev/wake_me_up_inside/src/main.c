#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/evp.h>

uint64_t calculate_md5(unsigned char* buf, unsigned int buf_size)
{
    EVP_MD_CTX *mdctx;
    unsigned char *md5_digest;
    unsigned int md5_digest_len = EVP_MD_size(EVP_md5());
    uint32_t value = 0;

    // MD5_Init
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);

    // MD5_Update
    EVP_DigestUpdate(mdctx, buf, buf_size);

    // MD5_Final
    md5_digest = (unsigned char *)OPENSSL_malloc(md5_digest_len);
    EVP_DigestFinal_ex(mdctx, md5_digest, &md5_digest_len);
    EVP_MD_CTX_free(mdctx);

    // return uint32_t
    value |= md5_digest[12] << 24;
    value |= md5_digest[13] << 16;
    value |= md5_digest[14] << 8;
    value |= md5_digest[15];
    return value;
}

// Handler for when time is up
void alarmHandler(int pass) {
    puts(":(");
    exit(1);
}

// Point to alarmHandler for SIGALRM and
// disable buffering on I/O
void setup() {
    struct sigaction act;
    act.sa_handler = alarmHandler;
    sigaction(SIGALRM, &act, NULL);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

// 0 - md5(flag[i]) & 0xffffffff
uint32_t thing[26] = {
    0xb0de2cb4,
    0x4cec9c5f,
    0xe91f6e53,
    0xb0de2cb4,
    0x949a9b62,
    0xca9bbafa,
    0x6fb0cba3,
    0x6fb0cba3,
    0x6fb0cba3,
    0x9688d99f,
    0xb319ffce,
    0xd3cf0fcc,
    0x4cec9c5f,
    0x06789b26,
    0x06789b26,
    0xf7bae229,
    0x17be13ce,
    0xb319ffce,
    0x6fb0cba3,
    0x9688d99f,
    0xb319ffce,
    0x4dfec4cd,
    0x06789b26,
    0xf7bae229,
    0x0d58450d,
    0x55fb6a31,
};

int main(){
    uint32_t x;
    char input_buf[32];
    setup();
    printf("> ");
    fgets(input_buf, 27, stdin);
    puts("");

    // win if md5sum(flag[i]) + thing[i] == 0
    for (int i = 0; i < 26; i++) {
        x = calculate_md5(&input_buf[i], 1) + thing[i];
        alarm(1);
        sleep(x);
    }

    puts(":)");
    return 0;
}
