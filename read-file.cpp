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

void download() {
    //FILE* file = popen("wget -r -np -A .txt http://www.hackershandbook.org/1000/","r");
    //FILE* file = popen("curl http://az.lib.ru/f/fet_a_a/text_0042.shtml", "rw");
    FILE *file = popen("curl http://az.lib.ru/f/fet_a_a/text_0042.shtml", "r");
    //std::vector<uint8_t> buf;
    std::string buf;
    buf.reserve(BUF_SIZE);
    //fread(
    printf("file %p\n", file);
    auto filesize = ftell(file);

    std::fstream outfile(OUT_FNAME, outfile.binary | outfile.out | outfile.trunc);
    if (!outfile.is_open()) {
        std::string msg = "Could not open ";
        msg += OUT_FNAME;
        msg += " file.";
        throw std::runtime_error(msg);
    }

    int sleeptime = 2;
    size_t ret = 0;
    sleep(sleeptime);
    ret = fread(&buf[0], BUF_SIZE, 1, file);
    sleep(sleeptime);
    ret = fread(&buf[0], BUF_SIZE, 1, file);
    sleep(sleeptime);
    ret = fread(&buf[0], BUF_SIZE, 1, file);
    sleep(sleeptime);
    ret = fread(&buf[0], BUF_SIZE, 1, file);

    outfile << "textxtetx" << std::endl;
    outfile << buf << std::endl;
    outfile << "textxtetx" << std::endl;

    printf("ret %ld\n", ret);

    // XXX нет проверки на переполнение знакового значения
    printf("filesize %d\n", (int)filesize);
    //fclose(file);
    pclose(file);
}

int main() {
    download();
    return EXIT_SUCCESS;
}
