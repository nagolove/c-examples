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
#include <iostream>
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
//#include <bits/stdc++.h>

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

//const uint BLOCK_SIZE = 1024 * 1000;
const uint BLOCK_SIZE = 8;

std::string check_error_number(int n, bool *found = nullptr) {

    const std::map<int, std::string> code2str = {
        { E2BIG, "bla" },
        { E2BIG, "Argument list too long" },
        { EACCES, "Permission denied "},
        { EADDRINUSE, "Address in use" },
        { EADDRNOTAVAIL, "Address not available"},
        { EAFNOSUPPORT, "Address family not supported"},
        { EAGAIN, "Resource unavailable, try again"},
        { EALREADY, "Connection already in progress"},
        { EBADF, "Bad file descriptor",},
        { EBADMSG, "Bad message",},
        { EBUSY, "Device or resource busy"},
        { ECANCELED, "Operation canceled"},
        { ECHILD, "No child processes"},
        { ECONNABORTED, "Connection aborted"},
        { ECONNREFUSED, "Connection refused"},
        { ECONNRESET, "Connection reset"},
        { EDEADLK, "Resource deadlock would occur"},
        { EDESTADDRREQ, "Destination address required"},
        { EDOM, "Mathematics argument out of domain of function"},
        { EEXIST, "File exists"},
        { EFAULT, "Bad address"},
        { EFBIG, "File too large"},
        { EHOSTUNREACH, "Host is unreachable"},
        { EIDRM, "Identifier removed"},
        { EILSEQ, "Illegal byte sequence"},
        { EINPROGRESS, "Operation in progress"},
        { EINTR, "Interrupted function"},
        { EINVAL, "Invalid argument"},
        { EIO, "I/O error"},
        { EISCONN, "Socket is connected"},
        { EISDIR, "Is a directory"},
        { ELOOP, "Too many levels of symbolic links"},
        { EMFILE, "File descriptor value too large"},
        { EMLINK, "Too many links"},
        { EMSGSIZE, "Message too large"},
        { ENAMETOOLONG, "Filename too long"},
        { ENETDOWN, "Network is down"},
        { ENETRESET, "Connection aborted by network"},
        { ENETUNREACH, "Network unreachable"},
        { ENFILE, "Too many files open in system"},
        { ENOBUFS, "No buffer space available"},
        { ENODATA, "No message is available on the STREAM head read queue"},
        { ENODEV, "No such device"},
        { ENOENT, "No such file or directory"},
        { ENOEXEC, "Executable file format error"},
        { ENOLCK, "No locks available"},
        { ENOLINK, "Link has been severed"},
        { ENOMEM, "Not enough space"},
        { ENOMSG, "No message of the desired type"},
        { ENOPROTOOPT, "Protocol not available"},
        { ENOSPC, "No space left on device"},
        { ENOSR, "No STREAM resources"},
        { ENOSTR, "Not a STREAM"},
        { ENOSYS, "Function not supported"},
        { ENOTCONN, "The socket is not connected"},
        { ENOTDIR, "Not a directory"},
        { ENOTEMPTY, "Directory not empty"},
        { ENOTRECOVERABLE, "State not recoverable"},
        { ENOTSOCK, "Not a socket"},
        { ENOTSUP, "Not supported"},
        { ENOTTY, "Inappropriate I/O control operation"},
        { ENXIO, "No such device or address"},
        { EOPNOTSUPP, "Operation not supported on socket"},
        { EOVERFLOW, "Value too large to be stored in data type"},
        { EOWNERDEAD, "Previous owner died"},
        { EPERM, "Operation not permitted"},
        { EPIPE, "Broken pipe"},
        { EPROTO, "Protocol error"},
        { EPROTONOSUPPORT, "Protocol not supported"},
        { EPROTOTYPE, "Protocol wrong type for socket"},
        { ERANGE, "Result too large"},
        { EROFS, "Read-only file system"},
        { ESPIPE, "Invalid seek"},
        { ESRCH, "No such process"},
        { ETIME, "Stream ioctl() timeout"},
        { ETIMEDOUT, "Connection timed out"},
        { ETXTBSY, "Text file busy"},
        { EWOULDBLOCK, "Operation would block"},
        { EXDEV, "Cross-device link"}, 
    };

    auto search = code2str.find(n);
    if (search == code2str.end()) {
        if (found)
            *found = false;
        return std::string("Error code not found.");
    } else {
        if (found)
            *found = true;
        return search->second;
    }
}

void check_error() {
    double somenumber = std::log(8);

    printf("error number: %d\n", check_error_number(errno));

    std::cout << "errno " << errno << '\n';
    std::cout << "strerror() before nan: " << std::strerror(errno) << '\n';
    double nan = std::log(-1.0);
    std::cout << "errno after " << errno << '\n';
    std::cout << "code2str() after " << check_error_number(errno) << '\n';
    if (errno == EDOM) {
        std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
        std::setlocale(LC_MESSAGES, "de_DE.utf8");
        std::cout << "In German: " << std::strerror(errno) << '\n';
        std::setlocale(LC_MESSAGES, "ru_RU.utf8");
        std::cout << "In Russian: " << std::strerror(errno) << '\n';
    }
}

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

    check_error();

        /*
    std::string data;
    data = read2mem("t1.txt");
    printf("data '%s'\n", data.c_str());

    data = read2mem("t2.txt");
    printf("data '%s'\n", data.c_str());

    data = read2mem("data-min.txt");
    printf("data '%s'\n", data.c_str());

    // FIXME
    // этот пример не работает
    //data = read2mem("simpledata.txt");
    data = read2mem("simpledata-half.txt");
    printf("data '%s'\n", data.c_str());

    // */
}

void test_passThroughPipe() {
    //TODO put some code here ..
    //std::string buf;
    //auto utf8str = passThroughPipe("iconv -f \"windows-1251\" -t \"utf-8\" .", buf);
}

void test_download() {
    //download("curl http://az.lib.ru/f/fet_a_a/text_0042.shtml");
}

// какие команды распознавать?
void decodeCMD(int argc, const char **argv) {
    printf("argc %d\n", argc);
    //for (int i = argc - 0; i >= 0; --i) {
    //for (int i = argc - 0; i >= 0; --i) {
    for (int i = 0; i < argc; i++) {
        printf("i = %d, str = %s\n", i, argv[i]);
        printf("%s\n", argv[i]);
    }
}

int main(int argc, const char **argv) {
    try {

        decodeCMD(argc, argv);

        test_read2mem();
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
    //*/
    return EXIT_SUCCESS;
}
