#include <iostream>
#include <nlohmann/json.hpp>
#include "Node.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>

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


	std::cout << "Input file: " << output_name << std::endl;

	std::ifstream i(input_name);
	std::ofstream o(output_name);

	// Start parsing
	try {

		nlohmann::json input_json;
		i >> input_json;

		auto parse_res = treetask::parse_children(input_json);

		if (parse_res.first == treetask::status_t::OK)
		{

			auto mirror_obj = parse_res.second;
			
			// Printing
			std::cout << "Incoming struct: " << std::endl;
			(*mirror_obj).print();

			// Serialising
			nlohmann::json mirror_json;

			(*mirror_obj).serialise(mirror_json);

			o << std::setw(4) << mirror_json << std::endl;
			
			std::cout << "Serialised to: "<< input_name << std::endl;
		}
		else {
			std::cout << "Parsed failed with code: " << parse_res.first << std::endl;
			std::cout << "Please provide a proper JSON. Aborting." << std::endl;
			return 2;
		}
	}
	catch (nlohmann::json::exception e) {
		std::cout << "Error occured while input JSON parsing : " << std::endl 
			<< e.what() << std::endl;
		return 2;
	}

	return 0;
}

