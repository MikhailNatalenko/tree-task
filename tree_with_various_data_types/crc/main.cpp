#include <iostream>
#include <nlohmann/json.hpp>
#include "Node.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>

namespace po = boost::program_options;


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

	std::string input_name, output_name;

	if (vm.count("input")) {
		input_name = vm["input"].as<std::string>();

	}
	else {
		std::cout << "Please, set Input file as follows: " << std::endl;
		std::cout << desc << std::endl;
		return 1;
	}

	if (vm.count("output")) {
		output_name = vm["output"].as<std::string>();

	}
	else {
		std::cout << "Please, set output file as follows: " << std::endl;
		std::cout << desc << std::endl;
		return 1;
	}

	std::cout << "Input file: "
		<< output_name << std::endl;

	std::ifstream i(input_name);
	std::ofstream o(output_name);

	nlohmann::json input_json;
	try {
		i >> input_json;

		auto parse_res = treetask::parse_children(input_json);
		if (parse_res.first == treetask::status_t::OK)
		{
			std::cout << "Incoming struct: " << std::endl;
			auto mirror_obj = parse_res.second;
			(*mirror_obj).print();
			nlohmann::json mirror_json;
			(*mirror_obj).serialise(mirror_json);
			std::string s2 = mirror_json.dump();
			o << std::setw(4) << mirror_json << std::endl;
			std::cout << "output file: "
				<< input_name << std::endl;
		}
		else {
			std::cout << "Parsed failed with code: " << parse_res.first << std::endl;
			std::cout << "Please provide a proper JSON. Aborting." << std::endl;
		}
	}
	catch (nlohmann::json::exception e) {
		std::cout << "Error occured while input JSON parsing : " << std::endl 
			<< e.what() << std::endl;
	}

	return 0;
}

