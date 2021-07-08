// Standard library includes {{{
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
//}}}
//#include <bits/stdc++.h>

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

// Unix includes {{{
#include <unistd.h>
#include <sys/stat.h>
//}}}

#include <iconv.h>

// Constants {{{
const uint32_t BUF_SIZE = 1024;
const char *OUT_FNAME = "data.txt";
const int sleeptime = 2;
const int pipeReadDelay = 100;
//}}}

using std::string;

// Exception handling classes {{{
class Error_CouldNotOpen: public std::runtime_error {
//{{{
public:
    Error_CouldNotOpen(const string& msg): std::runtime_error(msg) {
    };
    ~Error_CouldNotOpen() {
    }
};
//}}}
//
//}}}

/*
 * Возвращает строку с описанием ошибки по номеру. Дополнительный параметр -
 * флаг, указывающий на найдена-ли строка с ошибкой.
 */
std::string make_error_string(int n, bool *found = nullptr) {
    //{{{

    //{{{
    const std::map<int, std::string> code2str = {
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
    //}}}

    auto search = code2str.find(n);
    if (search == code2str.end()) {
        if (found)
            *found = false;
        return std::string("Error code not found: " + std::to_string(n));
    } else {
        if (found)
            *found = true;
        return search->second;
    }
    //}}}
}

/*
 * Меняет кодировку. Возвращает истину при успехе.
 */
bool decodeString(const char* to, const char* from, const string& instr, string& outstr) {
    //{{{
    if (errno != 0)
        throw std::runtime_error("errno is not set to 0 before call decodeString()");

    iconv_t convdescriptor = iconv_open(to, from);

    if (errno != 0) {
        if (convdescriptor != (iconv_t)(-1))
                iconv_close(convdescriptor);
        throw std::runtime_error(make_error_string(errno));
    }

    printf("convdescriptor %p\n", (void*)convdescriptor);

    // XXX Что за тройка? Как узнать сколько памяти понадобится?
    //const int wide = 3;
    //outstr.resize(instr.size() * wide);
    outstr.resize(instr.size());

    //const char* in[1] = {
    char *in[1] = {
        (char*)instr.data(),
    };

    char tmp[1024 * 1024] = {0, };
    char *out[1] = {
        tmp,
    };
    char *out2[2][64] = {
        {0, },
        {0, },
    };
    char buf[128] = {0, };
    char *pbuf = buf;
    printf("instr '%s'\n", instr.c_str());
    size_t insize = instr.size();
    printf("insize %lu\n", insize);
    size_t outsize = outstr.size(); // как узнать какого размера потребуется буфер?

    //size_t ret = iconv(convdescriptor, in, &insize, (char**)&tmp, &outsize);
    //size_t ret = iconv(convdescriptor, in, &insize, tmp, &outsize);
    //size_t ret = iconv(convdescriptor, in, &insize, (char**)out2, &outsize);
    size_t ret = iconv(convdescriptor, in, &insize, &pbuf, &outsize);

    if (errno != 0)
        throw std::runtime_error(make_error_string(errno));

    printf("out %s\n", out[0]);
    printf("insize %lu\n", outsize);
    printf("outsize %lu\n", outsize);
    printf("ret value %lu\n", ret);
    iconv_close(convdescriptor);
    return ret == 0;
    //}}}
}

/*
 * Пропускает databuf через команду используя трубу. Возвращает вывод команды в
 * виде строки.
 */
// TODO в случае ошибки должен кидать исключение Error_CouldNotOpen
std::string passThroughPipe(const std::string& command, const std::string& databuf) {
    //{{{

    FILE *file = popen(command.c_str(), "wr");
    if (!file)
        throw Error_CouldNotOpen(command);

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
    //}}}
}

/*
 * Скачивает текстовый файл из интернета и возвращает в виде строки символов.
 */
void download(const std::string& url) {
    // {{{
    FILE *file = popen(url.c_str(), "r");
    //std::vector<char> buf;
    std::string buf;
    buf.reserve(BUF_SIZE);
    //printf("file %p\n", (void*)file);
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
    //}}}
}

//const uint BLOCK_SIZE = 1024 * 1000;
const uint BLOCK_SIZE = 8;

void test_decodeString() {
    string in("входная строка"), out;
    printf("out '%s'\n", out.c_str());
    int ret = decodeString("UTF-8", "CP1251", in, out);
    //int ret = 0;
    printf("decodeString() =  %s\n", ret ? "true" : "false");
    printf("decoded: '%s'\n", out.c_str());
}

void check_error() {
    double somenumber = std::log(8);
    printf("%f\n", somenumber + 1);

    printf("error str: %s\n", make_error_string(errno).c_str());

    std::cout << "errno " << errno << '\n';
    std::cout << "strerror() before nan: " << std::strerror(errno) << '\n';
    double nan = std::log(-1.0);
    printf("nan %f]\n", nan);
    std::cout << "errno after " << errno << '\n';
    std::cout << "code2str() after " << make_error_string(errno) << '\n';
    if (errno == EDOM) {
        std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
        std::setlocale(LC_MESSAGES, "de_DE.utf8");
        std::cout << "In German: " << std::strerror(errno) << '\n';
        std::setlocale(LC_MESSAGES, "ru_RU.utf8");
        std::cout << "In Russian: " << std::strerror(errno) << '\n';
    }
}

#define PRINT_ERROR_CODE    (printf("%s\n", check_error_number(errno).c_str()))

// TODO проверить ошибки считывания последнего кусочка файла
// Считывает содержимое файла в память и возвращает строковый объекта. В случае
// ошибки бросает исключение Error_CouldNotOpen

std::string read2mem(const std::string& fname) {
    //{{{
    size_t ret = 0;
    FILE *file = fopen(fname.c_str(), "r");
    if (!file)
        throw Error_CouldNotOpen(fname);
    std::string buf, resbuf;
    buf.reserve(BLOCK_SIZE);
    buf.resize(BLOCK_SIZE);
    // TODO добавить проверку на считывание маленького куска
    ret = fread(buf.data(), 1, BLOCK_SIZE, file);
    while (ret > 0) {
        resbuf.append(buf);
        buf.resize(BLOCK_SIZE);
        ret = fread(buf.data(), 1, BLOCK_SIZE, file);
        if (ret > 0)
            buf.resize(ret);
    }
    if (ferror(file) != 0) {
        fclose(file);
        throw std::runtime_error("ferror() got non zero on " + fname);
    }
    fclose(file);
    return resbuf;
}

#undef PRINT_ERROR_CODE

void test_read2mem() {
    //{{{
    std::string data;
    //data = read2mem("t1.txt");
    //printf("data '%s'\n", data.c_str());

    data = read2mem("reference.txt");
    FILE *out = fopen("out.txt", "w");
    fwrite(data.c_str(), data.size(), 1, out);
    fclose(out);
    //}}}
}

void test_passThroughPipe() {
    //TODO put some code here ..
    std::string buf = read2mem("reference.txt");
    //printf("%s", buf.c_str());
    auto utf8str = passThroughPipe("iconv -f \"windows-1251\" -t \"utf-8\" .", buf);
    printf("%s\n", utf8str.c_str());
}

void test_download() {
    //download("curl http://az.lib.ru/f/fet_a_a/text_0042.shtml");
}

// какие команды распознавать?
void decodeCMD(int argc, const char **argv) {
    //printf("argc %d\n", argc);
    //for (int i = argc - 0; i >= 0; --i) {
    //for (int i = argc - 0; i >= 0; --i) {
    for (int i = 0; i < argc; i++) {
        //printf("i = %d, str = %s\n", i, argv[i]);
        //printf("%s\n", argv[i]);
    }
}

int main(int argc, const char **argv) {
    signal(SIGSEGV, handler);
    try {

        decodeCMD(argc, argv);

        //test_read2mem();
        //test_passThroughPipe();
        test_decodeString();
        //test_download();

    } catch (const Error_CouldNotOpen& e) {
        printf("Sorry, could not open file '%s'\n", e.what());
    } catch (const std::overflow_error& e) {
        fprintf(stderr, "Main exception handler. Overflow error: %s\n", e.what());
    } catch (const std::runtime_error& e) {
        fprintf(stderr, "Main exception handler. Runtine error: %s\n", e.what());
    } catch (const std::exception& e) {
        fprintf(stderr, "Main exception handler. Exception: %s\n", e.what());
        // this executes if f() throws std::logic_error (base class rule)
    } catch (...) {
        fprintf(stderr, "Main exception handler - unknown error. No implemented exceptions avaible.\n");
    }
    //*/
    return EXIT_SUCCESS;
}
