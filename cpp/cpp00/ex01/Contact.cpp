/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:17:20 by eusatiko          #+#    #+#             */
/*   Updated: 2025/01/24 14:17:22 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
    : first_name(""), last_name(""), nickname(""), phone(""), secret("") {}

Contact::Contact(std::string fn, std::string ln, std::string nn, std::string ph, std::string sc)
    : first_name(fn), last_name(ln), nickname(nn), phone(ph), secret(sc) {}

std::string Contact::get_first_name()
{
    return first_name;
}

std::string Contact::get_last_name()
{
    return last_name;
}

std::string Contact::get_nickname()
{
    return nickname;
}

std::string Contact::get_phone()
{
    return phone;
}
std::string Contact::get_secret()
{
    return secret;
}
