#pragma once
#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
	std::string m_name = "NONE";
	std::string m_type = "NONE"; // either START or END for keypress/keyrelease

public:
	Action();
	Action(const std::string& name, const std::string& type);

	const std::string& name() const;
	const std::string& type() const;
	std::string toString() const;
};



#endif // !ACTION_H
