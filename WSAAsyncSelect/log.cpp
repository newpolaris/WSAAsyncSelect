#include "stdafx.h"

#include <string>
#include <sstream>
#include <istream>
#include "log.h"

namespace echoservice {
	using std::string;

	output& output::operator<<(const string str)
	{
		return operator<<(wstring(str.begin(), str.end()));
	}

	output& output::operator<<(const wstring& str)
	{
		if (m_list == nullptr)
			return *this;

		m_list->SetCurSel(m_list->InsertString(0, str.c_str()));
		return *this;
	};
}