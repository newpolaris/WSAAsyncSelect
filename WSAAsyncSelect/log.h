#pragma once
#include <string>

class CListBox;

namespace echoservice {
	using std::string;
	using std::wstring;

	static string m_endl = "\n";

	class output
	{
	public:
		output() {}
		void init(CListBox* list) { m_list = list; }
		output& operator<<(const string str);
		output& operator<<(const wstring& str);
	private:
		CListBox* m_list = nullptr;
	};

} // namespace echoservice {