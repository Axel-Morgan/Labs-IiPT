#include "pch.h"
#include <iostream>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace std;

namespace beast = boost::beast; 
namespace http = beast::http; 
namespace net = boost::asio; 
using tcp = net::ip::tcp; 

int main()
{
	setlocale(LC_ALL, "Russian");
	try // Обработка исключений
	{
		int number_1 = 0, number_2 = 0;
		char operation;
		bool open = false; 
		string const host = "157.230.27.215"; // Хост
		string const port = "80"; // Порт
		stringstream url;

		cout << "Введите 1-ое число: "; cin >> number_1;
		while (open == false)
		{
			cout << "Введите операцию (введите + или -): "; cin >> operation;
			if ((operation == '+') || (operation == '-'))
			{
				open = true;
			}

			else
			{
				cout << "Выберите знак + или -";
			}
		}
		cout << "Введите 2-ое число: "; cin >> number_2;

			if (operation == '+') 
			{
				url << "/calc/sum/" << number_1 << "/" << number_2;
			}

			if (operation == '-')
			{
				url << "/calc/diff/" << number_1 << "/" << number_2;
			}
	
		net::io_context ioc; 
		string const target = url.str();
		int const version = 11;
		cout << target;

		tcp::resolver resolver(ioc); 
		auto const results = resolver.resolve(host, port);
		beast::tcp_stream stream(ioc);
		stream.connect(results);

		http::request<http::string_body> req{ http::verb::get, target, version }; 
		req.set(http::field::host, host);
		req.set(http::field::user_agent, "gg/test");

		http::write(stream, req); 

		beast::flat_buffer buffer; 

		http::response<http::dynamic_body> res; 

		http::read(stream, buffer, res); 
		cout << res << endl;

		beast::error_code ec; // Закрытие сокета
		stream.socket().shutdown(tcp::socket::shutdown_both, ec);

		if (ec && ec != beast::errc::not_connected) // Проверка на наличие ошибки соединения
			throw beast::system_error{ ec };
	}

	catch (std::exception const& e) // Возможная ошибка
	{
		cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}