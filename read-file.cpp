#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <charconv>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <codecvt>
#include <complex>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include <unistd.h>

const uint32_t BUF_SIZE = 1024;
const char *OUT_FNAME = "data.txt";
const int sleeptime = 2;

/*
 * Скачивает текстовый файл из интернета и возвращает в виде строки символов.
 */
void download(const std::string& url) {
    FILE *file = popen(url.c_str(), "r");
    std::vector<char> buf;
    //std::string buf;
    buf.reserve(BUF_SIZE);
    printf("file %p\n", file);
    auto filesize = ftell(file);

    std::fstream outfile(OUT_FNAME, outfile.binary | outfile.out | outfile.trunc);
    if (!outfile.is_open()) {
        std::string msg = "Could not open ";
        msg += OUT_FNAME;
        msg += " file.";
        throw std::runtime_error(msg);
    }

    size_t ret = 0;

    usleep(sleeptime);
    ret = fread(buf.data(), BUF_SIZE, 1, file);

    // Цикл чтения и ожидания
    //do {
        //outfile.write(&buf[0], BUF_SIZE);
        //printf("ret %d\n", ret);
    //} while (ret != 0);
    while (ret != 0) {
        outfile.write(&buf[0], BUF_SIZE);
        usleep(sleeptime);
        ret = fread(buf.data(), BUF_SIZE, 1, file);
        printf("ret %d\n", ret);
    }

    //char simplebuf[1024] = {0, };
    //ret = fread(simplebuf, BUF_SIZE, 1, file);
    //printf("simplebuf '%s'\n", simplebuf);

    /*
     *sleep(sleeptime);
     *ret = fread(&buf[0], BUF_SIZE, 1, file);
     *sleep(sleeptime);
     *ret = fread(&buf[0], BUF_SIZE, 1, file);
     *sleep(sleeptime);
     *ret = fread(&buf[0], BUF_SIZE, 1, file);
     */

    outfile << "textxtetx" << std::endl;
    //outfile << buf << std::endl;
    outfile << "textxtetx" << std::endl;

    printf("ret %ld\n", ret);

    // XXX нет проверки на переполнение знакового значения
    printf("filesize %d\n", (int)filesize);
    //fclose(file);
    pclose(file);
}

int main() {
    download("curl http://az.lib.ru/f/fet_a_a/text_0042.shtml");
    return EXIT_SUCCESS;
}
