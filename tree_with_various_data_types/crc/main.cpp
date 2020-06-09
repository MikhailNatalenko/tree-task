#include <iostream>
#include <nlohmann/json.hpp>
#include "Node.h"
//#include <boost/program_options.hpp>

//namespace po = boost::program_options;

void test_memleaks()
{
    for (int i = 0; i < 100; i++)
    {
        treetask::Node<int> a(3);
        auto b = std::make_shared <treetask::Node<std::string>>("river");
        auto c = std::make_shared <treetask::Node<float>>(0.8);

        a.add_child(std::make_shared<treetask::Node<int>>(2));
        a.add_child(std::make_shared<treetask::Node<float>>(3.1415));

        b->add_child(std::make_shared<treetask::Node<std::string>>("Agidel"));
        b->add_child(std::make_shared<treetask::Node<int>>(8));
        b->add_child(std::make_shared<treetask::Node<float>>(5.0));

        c->add_child(std::make_shared<treetask::Node<float>>(0.2));
        c->add_child(std::make_shared<treetask::Node<int>>(3));
        b->add_child(c);
        a.add_child(b);
        nlohmann::json j;
        a.serialise(j);
        std::string s = j.dump();
        nlohmann::json mirror = nlohmann::json::parse(s);

        auto parse_res = treetask::parse_children(mirror);
        if (parse_res.first == treetask::status_t::OK)
        {
            auto mirror_obj = parse_res.second;

            nlohmann::json mirror_json;
            (*mirror_obj).serialise(mirror_json);
            std::string s2 = mirror_json.dump();
        }
    }
}

#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int ac, char* av[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("input,i", po::value<std::string>(), "input file")
        ("output,o", po::value<std::string>(), "output file")
        ;

    po::variables_map vm;
    try {

    po::store(po::parse_command_line(ac, av, desc), vm);
    }
    catch (po::unknown_option e)
    {
        std::cout << e.what() << std::endl;
        std::cout << desc << std::endl;
    }
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("input")) {
        std::cout << "Input file: "
            << vm["input"].as<std::string>() << std::endl;
    }
    else {
        std::cout << "Input file was not set." << std::endl;
    }

    if (vm.count("output")) {
        std::cout << "output file: "
            << vm["output"].as<std::string>() << std::endl;
    }
    else {
        std::cout << "output file was not set.\n";
    }
    //try {

    //    po::options_description desc("Allowed options");
    //    desc.add_options()
    //        ("help", "produce help message")
    //        ("compression", po::value<double>(), "set compression level")
    //        ;

    //    po::variables_map vm;
    //    po::store(po::parse_command_line(ac, av, desc), vm);
    //    po::notify(vm);

    //    if (vm.count("help")) {
    //        std::cout << desc << "\n";
    //        return 0;
    //    }

    //    if (vm.count("compression")) {
    //        std::cout << "Compression level was set to "
    //            << vm["compression"].as<double>() << ".\n";
    //    }
    //    else {
    //        std::cout << "Compression level was not set.\n";
    //    }
    //}
    //catch (std::exception & e) {
    //    std::cerr << "error: " << e.what() << "\n";
    //    return 1;
    //}
    //catch (...) {
    //    std::cerr << "Exception of unknown type!\n";
    //}
    //test_memleaks();
    std::cout << "Hello " << std::endl;
    treetask::Node<int> a(3);
    auto b = std::make_shared <treetask::Node<std::string>>("lake");
    auto c = std::make_shared <treetask::Node<float>>(0.8);

    a.add_child(std::make_shared<treetask::Node<int>>(2));
    a.add_child(std::make_shared<treetask::Node<float>>(3.1415));

    b->add_child(std::make_shared<treetask::Node<std::string>>("Agidel"));
    b->add_child(std::make_shared<treetask::Node<int>>(8));
    b->add_child(std::make_shared<treetask::Node<float>>(5.0));

    c->add_child(std::make_shared<treetask::Node<float>>(0.2));
    c->add_child(std::make_shared<treetask::Node<int>>(3));
    b->add_child(c);
    a.add_child(b);
    nlohmann::json j;
    a.serialise(j);
    std::string s = j.dump();

    std::cout << s << std::endl;

    nlohmann::json mirror = nlohmann::json::parse(s);

    auto parse_res = treetask::parse_children(mirror);
    if (parse_res.first == treetask::status_t::OK)
    {
        auto mirror_obj = parse_res.second;

        std::cout << "parse_res: " << std::endl << std::endl;
        nlohmann::json mirror_json;
        (*mirror_obj).serialise(mirror_json);
        std::string s2 = mirror_json.dump();
        std::cout << s2 << std::endl;
    }

    return 0;
}

