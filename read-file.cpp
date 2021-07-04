#include <algorithm>
#include <any>
#include <array>
#include <atomic>
//#include <bits/stdc++.h>
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
#include <sys/stat.h>

const uint32_t BUF_SIZE = 1024;
const char *OUT_FNAME = "data.txt";
const int sleeptime = 2;
const int pipeReadDelay = 100;

bool isFileExist(const std::string &fname) {
    return false;
}

/*

FILE *stream = fopen("somefname.txt", "r");
int fd = fileno(stream);

*/


/*
 * Пропускает databuf через команду используя трубу. Возвращает вывод команды в
 * виде строки.
 */
// TODO в случае ошибки должен кидать исключение
std::string passThroughPipe(const std::string& command, const std::string& databuf) {

    FILE *file = popen(command.c_str(), "wr");

    //TODO проверить на неудачное выполнение команды
    std::string buf;
    buf.reserve(BUF_SIZE);

    size_t ret = 0;
    std::string internalBuf;

    usleep(pipeReadDelay);
    ret = fread(buf.data(), 1, BUF_SIZE, file);

    // Цикл чтения и ожидания
    // записать в трубу
    // подождать
    // прочитать из трубы
    
    while (ret != 0) {

        //outfile.write(&buf[0], BUF_SIZE);
        
        usleep(pipeReadDelay);
        ret = fread(buf.data(), 1, BUF_SIZE, file);

        //printf("ret %d\n", ret);
        //outfile.write(&buf[0], BUF_SIZE);
        //outfile.write(&utf8str[0], utf8str.size());
    }

    pclose(file);
    return "";
}

/*
 * Скачивает текстовый файл из интернета и возвращает в виде строки символов.
 */
void download(const std::string& url) {
    FILE *file = popen(url.c_str(), "r");
    //std::vector<char> buf;
    std::string buf;
    buf.reserve(BUF_SIZE);
    printf("file %p\n", file);
    //auto filesize = ftell(file);

    std::fstream outfile(OUT_FNAME, outfile.binary | outfile.out | outfile.trunc);
    if (!outfile.is_open()) {
        std::string msg = "Could not open ";
        msg += OUT_FNAME;
        msg += " file.";
        throw std::runtime_error(msg);
    }

    size_t ret = 0;

    usleep(sleeptime);
    ret = fread(buf.data(), 1, BUF_SIZE, file);

    // Цикл чтения и ожидания
    //do {
        //outfile.write(&buf[0], BUF_SIZE);
        //printf("ret %d\n", ret);
    //} while (ret != 0);
    while (ret != 0) {
        outfile.write(&buf[0], BUF_SIZE);
        usleep(sleeptime);
        ret = fread(buf.data(), BUF_SIZE, 1, file);
        //printf("ret %d\n", ret);

        auto utf8str = passThroughPipe("iconv -f \"windows-1251\" -t \"utf-8\" .", buf);
        //outfile.write(&buf[0], BUF_SIZE);
        outfile.write(&utf8str[0], utf8str.size());
    }

    auto utf8str = passThroughPipe("iconv -f \"windows-1251\" -t \"utf-8\" .", buf);
    //outfile.write(&buf[0], BUF_SIZE);
    outfile.write(&utf8str[0], utf8str.size());

    outfile << std::endl;

    //char simplebuf[1024] = {0, };
    //ret = fread(simplebuf, BUF_SIZE, 1, file);
    //printf("simplebuf '%s'\n", simplebuf);

    // XXX нет проверки на переполнение знакового значения
    //printf("filesize %d\n", (int)filesize);
    
    pclose(file);
}

//const uint BLOCK_SIZE = 1024;
const uint BLOCK_SIZE = 8;

// TODO проверить ошибки считывания последнего кусочка файла
// Считывает содержимое файла в память и возвращает строковый объекта. В случае
// ошибки бросает исключение std::exception
std::string read2mem(const std::string& fname) {
    size_t ret = 0;
    FILE *file = fopen(fname.c_str(), "r");
    std::string buf, resbuf;
    buf.reserve(BLOCK_SIZE);
    buf.resize(BLOCK_SIZE);

    if (file == nullptr || ferror(file) != 0) {
        fclose(file);
        throw std::runtime_error("Could not read file " + fname);
    }

    // TODO добавить проверку на считывание маленького куска
    ret = fread(buf.data(), 1, BLOCK_SIZE, file);

    while (ret > 0) {
        //std::string oldbuf(buf);
        resbuf.append(buf);
        ret = fread(buf.data(), 1, BLOCK_SIZE, file);
        if (ret > 0)
            buf.resize(ret);
        //printf("buf '%s', ret = %lu\n", buf.c_str(), ret);
    }

    if (ferror(file) != 0) {
        fclose(file);
        throw std::runtime_error("ferror() got non zero on " + fname);
    }

    fclose(file);
    return resbuf;
}

void test_read2mem() {
    std::string data;
    data = read2mem("t1.txt");
    printf("data '%s'\n", data.c_str());

    data = read2mem("t2.txt");
    printf("data '%s'\n", data.c_str());

    data = read2mem("data-min.txt");
    printf("data '%s'\n", data.c_str());

    // этот пример не работает
    //data = read2mem("simpledata.txt");
    printf("data '%s'\n", data.c_str());
}

void test_passThroughPipe() {
    //TODO put some code here ..
    //std::string buf;
    //auto utf8str = passThroughPipe("iconv -f \"windows-1251\" -t \"utf-8\" .", buf);
}

void test_download() {
    //download("curl http://az.lib.ru/f/fet_a_a/text_0042.shtml");
}

// FIXME не работает
void decodeCMD(int argc, const char **argv) {
    printf("argc %d\n", argc);
    for (int i = argc - 0; i >= 0; --i) {
        printf("i = %d, str = %s\n", i, argv[i]);
        printf("%s\n", argv[i]);
    }
}

int main(int argc, const char **argv) {
    try {

        decodeCMD(argc, argv);

        //test_read2mem();
        //test_passThroughPipe();
        //test_download();

    } catch (const std::overflow_error& e) {
        // this executes if f() throws std::overflow_error (same type rule)
    } catch (const std::runtime_error& e) {
        // this executes if f() throws std::underflow_error (base class rule)
    } catch (const std::exception& e) {
        // this executes if f() throws std::logic_error (base class rule)
    } catch (...) {
        fprintf(stderr, "Unknown error. No implemented exceptions avaible.");
    }

    return EXIT_SUCCESS;
}
