#if 1
#include <iostream>

#include "./tokenizer.h"
#include "INPUT.h"
#include "Parser.h"
#include "eval_env.h"
int main(int argc, char* argv[]) {
    std::shared_ptr<EvalEnv> env{new EvalEnv};
    INPUT in;
    std::ifstream fin;
    if (argc == 1)
        in = std::cin;
    else {
        fin.open(argv[1]);
        if (fin.is_open())
            in = fin;
        else {
            std::cerr << "No file is opened!"
                      << "\n";
            std::exit(0);
        }
    }
    do {
        try {
            if (argc == 1) std::cout << ">>> ";
            std::string line;
            getline(in, line);
            if (line != "") {
                auto tokens = Tokenizer::tokenize(line);
                Parser parser(std::move(tokens));  // TokenPtr 不支持复制
                auto value = parser.parse();
                auto result = env->eval(std::move(value));
                if (argc == 1)
                    std::cout << result->toString()
                              << std::endl;  // 输出外部表示
            }
        } catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } while (in);
    ;
}
#else
#include <iostream>
#include <string>

#include"./parser.h"
#include "./value.h"
#include "./eval_env.h"
#include "./tokenizer.h"
#include"./builtins.h"

/*#include "rjsj_test.hpp"

struct TestCtx {
    std::string eval(std::string input) {
        auto tokens = Tokenizer::tokenize(input);
        Parser parser(std::move(tokens));
        auto value = parser.parse();
        return value->toString();
    }
};*/
#include "rjsj_test.hpp"
struct TestCtx {
    std::shared_ptr<EvalEnv> env{new EvalEnv};
    std::string eval(std::string input) {
        auto tokens = Tokenizer::tokenize(input);
        Parser parser(std::move(tokens));
        auto value = parser.parse();
        auto result = env->eval(std::move(value));
        return result->toString();
    }
};

int main() {
    //std::shared_ptr<EvalEnv> env;
    std::shared_ptr<EvalEnv> env{new EvalEnv};
    //RJSJ_TEST(TestCtx, Lv2, Lv2Only);
     //RJSJ_TEST(TestCtx, Lv2, Lv3);
    RJSJ_TEST(TestCtx, Lv2, Lv3, Lv4,Lv5,Lv5Extra,Lv6,Lv7,Lv7Lib,Sicp);
    while (true) {
        try { 
            std::cout << ">>> " ;
            std::string line;
            std::getline(std::cin, line);
            if (std::cin.eof()) {
                std::exit(0);
            }
            auto tokens = Tokenizer::tokenize(line);
            Parser parser(std::move(tokens));// TokenPtr 不支持复制
            auto value = parser.parse();
           
            auto result = env->eval(std::move(value));
            std::cout << result->toString() << std::endl;// 输出外部表示
        } catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        
    }
}

#endif
