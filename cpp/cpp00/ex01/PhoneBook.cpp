/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:18:16 by eusatiko          #+#    #+#             */
/*   Updated: 2025/01/28 12:37:51 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
    : size(0) {}

void PhoneBook::listen()
{
    std::string input;
    while (1)
    {
        if (std::cin.eof())
        {
            std::cout << std::endl;
			break;
        }
        std::cout << "Please enter command: ADD, SEARCH or EXIT" << std::endl;
        std::getline(std::cin, input);
        if (std::cin.eof())
			break;
        if (input == "ADD")
            add();
        else if (input == "SEARCH")
            search();
        else if (input == "EXIT")
            return (exit());
    }
}

std::string get_input(const std::string msg)
{
    std::string ret = "";

    while (!ret.size())
    {
        if (std::cin.eof())
            break;
        std::cout << msg;
        std::getline(std::cin, ret);
    }
    return ret;
}

void PhoneBook::add()
{
    std::string fn = get_input("First name: ");
    std::string ln = get_input("Last name: ");
    std::string nn = get_input("Nickname: ");
    std::string ph = "";
    while (ph.size() < 5)
    {
        ph = get_input("Phone (at least 5 digits): ");
        if (std::cin.eof())
			break;
        ph = check_phone(ph);
    }
    std::string se = get_input("Darkest secret: ");
    if (!se.size())
        return ;
    list[size % 8] = Contact(fn, ln, nn, ph, se);
    size ++;
    
}

void PhoneBook::search()
{
    int max = size < 8 ? size : 8;
    std::string spaces = "         ";
    std::cout << " __________ __________ __________ __________\n";
    std::cout << "|     index|first name| last name|  nickname|\n";
    for (int i=0; i < max; i++)
    {
        std::cout << "|" << spaces.substr(0, 10 - numdigits(i)) << i << "|"; 
        short_data(list[i].get_first_name());
        short_data(list[i].get_last_name());
        short_data(list[i].get_nickname());
        std::cout << std::endl;
    }
    std::cout << "|__________|__________|__________|__________|\n";
    if (!size)
        return ;
    std::string input;
    int idx = -1;
    while (idx < 0 || idx >= max)
    {
        input = get_input("Index of a contact to be displayed: ");
        if (std::cin.eof())
			return ;
        idx = get_idx(input);
    }
    full_data(list[idx]);
}

void PhoneBook::exit()
{       
    for (int i = 0; i < 8; i++)
        list[i] = Contact();
    size = 0;
}

/*Helper functions*/

std::string check_phone(std::string ph)
{
    int len = (int)ph.size();
    for (int i = 0; i < len; i++)
    {
        if (ph[i] < '0' || ph[i] > '9')
            return ("");
    }
    return ph; 
}

void short_data(std::string data)
{
    std::string::size_type len = data.size();
    std::string spaces = "         ";
    if (len < 11)
        std::cout << spaces.substr(0, 10 - len) << data << "|";
    else
        std::cout << data.substr(0, 9) << ".|";
}

void full_data(Contact c)
{
    std::cout << "First name: " << c.get_first_name() << std::endl;
    std::cout << "Last name: " << c.get_last_name() << std::endl;
    std::cout << "Nickname: " << c.get_nickname() << std::endl;
    std::cout << "Phone number: " << c.get_phone() << std::endl;
    std::cout << "Darkest secret: " << c.get_secret() << std::endl;
}

int get_idx(std::string input)
{
    int ret = 0;
    std::string::size_type i;
    for (i = 0; i < input.size(); i++)
    {
        if (input[i] < '0' || input[i] > '9')
            return (-1);
        ret *= 10;
        ret += input[i] - '0';
    }
    return ret;
}

int numdigits(int n) 
{
    if (!n) 
        return 1;
    int len = 0;
    while (n != 0) 
    {
        n /= 10;
        len++;
    }
    if (len > 10)
        return 10;
    return len;
}
