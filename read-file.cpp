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

void check_error_number() {

    std::map<int, std::string> code2str = {
        { E2BIG, "bla" },
    };
    /*
E2BIG
  
Argument list too long
(macro constant)
EACCES
  
Permission denied
(macro constant)
EADDRINUSE
  
Address in use
(macro constant)
EADDRNOTAVAIL
  
Address not available
(macro constant)
EAFNOSUPPORT
  
Address family not supported
(macro constant)
EAGAIN
  
Resource unavailable, try again
(macro constant)
EALREADY
  
Connection already in progress
(macro constant)
EBADF
  
Bad file descriptor
(macro constant)
EBADMSG
  
Bad message
(macro constant)
EBUSY
  
Device or resource busy
(macro constant)
ECANCELED
  
Operation canceled
(macro constant)
ECHILD
  
No child processes
(macro constant)
ECONNABORTED
  
Connection aborted
(macro constant)
ECONNREFUSED
  
Connection refused
(macro constant)
ECONNRESET
  
Connection reset
(macro constant)
EDEADLK
  
Resource deadlock would occur
(macro constant)
EDESTADDRREQ
  
Destination address required
(macro constant)
EDOM
 
Mathematics argument out of domain of function
(macro constant)
EEXIST
  
File exists
(macro constant)
EFAULT
  
Bad address
(macro constant)
EFBIG
  
File too large
(macro constant)
EHOSTUNREACH
  
Host is unreachable
(macro constant)
EIDRM
  
Identifier removed
(macro constant)
EILSEQ
  
Illegal byte sequence
(macro constant)
EINPROGRESS
  
Operation in progress
(macro constant)
EINTR
  
Interrupted function
(macro constant)
EINVAL
  
Invalid argument
(macro constant)
EIO
  
I/O error
(macro constant)
EISCONN
  
Socket is connected
(macro constant)
EISDIR
  
Is a directory
(macro constant)
ELOOP
  
Too many levels of symbolic links
(macro constant)
EMFILE
  
File descriptor value too large
(macro constant)
EMLINK
  
Too many links
(macro constant)
EMSGSIZE
  
Message too large
(macro constant)
ENAMETOOLONG
  
Filename too long
(macro constant)
ENETDOWN
  
Network is down
(macro constant)
ENETRESET
  
Connection aborted by network
(macro constant)
ENETUNREACH
  
Network unreachable
(macro constant)
ENFILE
  
Too many files open in system
(macro constant)
ENOBUFS
  
No buffer space available
(macro constant)
ENODATA
  
No message is available on the STREAM head read queue
(macro constant)
ENODEV
  
No such device
(macro constant)
ENOENT
  
No such file or directory
(macro constant)
ENOEXEC
  
Executable file format error
(macro constant)
ENOLCK
  
No locks available
(macro constant)
ENOLINK
  
Link has been severed
(macro constant)
ENOMEM
  
Not enough space
(macro constant)
ENOMSG
  
No message of the desired type
(macro constant)
ENOPROTOOPT
  
Protocol not available
(macro constant)
ENOSPC
  
No space left on device
(macro constant)
ENOSR
  
No STREAM resources
(macro constant)
ENOSTR
  
Not a STREAM
(macro constant)
ENOSYS
  
Function not supported
(macro constant)
ENOTCONN
  
The socket is not connected
(macro constant)
ENOTDIR
  
Not a directory
(macro constant)
ENOTEMPTY
  
Directory not empty
(macro constant)
ENOTRECOVERABLE
  
State not recoverable
(macro constant)
ENOTSOCK
  
Not a socket
(macro constant)
ENOTSUP
  
Not supported
(macro constant)
ENOTTY
  
Inappropriate I/O control operation
(macro constant)
ENXIO
  
No such device or address
(macro constant)
EOPNOTSUPP
  
Operation not supported on socket
(macro constant)
EOVERFLOW
  
Value too large to be stored in data type
(macro constant)
EOWNERDEAD
  
Previous owner died
(macro constant)
EPERM
  
Operation not permitted
(macro constant)
EPIPE
  
Broken pipe
(macro constant)
EPROTO
  
Protocol error
(macro constant)
EPROTONOSUPPORT
  
Protocol not supported
(macro constant)
EPROTOTYPE
  
Protocol wrong type for socket
(macro constant)
ERANGE
 
Result too large
(macro constant)
EROFS
  
Read-only file system
(macro constant)
ESPIPE
  
Invalid seek
(macro constant)
ESRCH
  
No such process
(macro constant)
ETIME
  
Stream ioctl() timeout
(macro constant)
ETIMEDOUT
  
Connection timed out
(macro constant)
ETXTBSY
  
Text file busy
(macro constant)
EWOULDBLOCK
  
Operation would block
(macro constant)
EXDEV
*/

void check_error() {
    double somenumber = std::log(8);
    std::cout << "errno " << errno << '\n';
    std::cout << "strerror() before nan: " << std::strerror(errno) << '\n';
    double nan = std::log(-1.0);
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
