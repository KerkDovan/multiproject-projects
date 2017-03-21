// Changeable code starts here. 

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string.h>
#include <tuple>
#include <vector>

#include "libs/easendmailobj.tlh"

#define stringify(str) stringify2(str)
#define stringify2(str) #str

// Changeable code stops here. 
	
#ifdef _LOCAL_MULTIPROJECT_

#include "multiproject.h"

namespace project {

	using namespace project::tools;
	using namespace project::tools::debugging;
	using namespace project::tools::debugging::format;

#else

#include <iostream>

#define breakpoint_if(...)
#define breakpoint
#define only_multiproject(...)
#define debug_output(...)
#define freopen_in(filename) freopen(filename, "r", stdin)
#define freopen_out(filename) freopen(filename, "w", stdout)
#define close_files

#endif

// Changeable code continues here. 

	using namespace std;
	using namespace EASendMailObjLib;

	typedef long long ll;
	typedef unsigned long long ull;

	typedef _bstr_t _T;

	int main() {
	#ifndef ONLINE_JUDGE
		freopen_in("input.txt");
		freopen_out("output.txt");
	#endif
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		::CoInitialize(NULL);

		IMailPtr oSmtp = NULL;
		oSmtp.CreateInstance("EASendMailObj.Mail");
		oSmtp->LicenseCode = _T("TryIt");

		// Set your gmail email address
		oSmtp->FromAddr = _T("iwannaberabbit@gmail.com");

		// Add recipient email address
		oSmtp->AddRecipientEx(_T("bogomolov.yuriy@gmail.com"), 0);

		// Set email subject
		oSmtp->Subject = _T("simple email from Visual C++ with gmail account");

		// Set email body
		oSmtp->BodyText = _T("this is a test email sent from Visual C++ project with Gmail");

		// Gmail SMTP server address
		oSmtp->ServerAddr = _T("smtp.gmail.com");

		// Use SSL 465 port, 
		oSmtp->ServerPort = 465;

		// detect SSL/TLS automatically
		oSmtp->SSL_init();

		// Gmail user authentication should use your 
		// Gmail email address as the user name. 
		// For example: your email is "gmailid@gmail.com", then the user should be "gmailid@gmail.com"
		oSmtp->UserName = _T("iwannaberabbit@gmail.com");
		oSmtp->Password = _T("doyouwannabeRABBIT,guy?");

		cout << (_T("Start to send email via gmail account ...\r\n"));

		if (oSmtp->SendMail() == 0)
		{
			cout << (_T("email was sent successfully!\r\n"));
		}
		else
		{
			cout << (_T("failed to send email with the following error: %s\r\n"),
				(const TCHAR*)oSmtp->GetLastErrDescription());
		}

		if (oSmtp != NULL)
			oSmtp.Release();

		close_files;
		return 0;
	}

// Changeable code ends here

#ifdef _LOCAL_MULTIPROJECT_

} // namespace project

#endif