#include <iostream>         // for the input/output
#include <stdlib.h>         // for the getenv call
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#define LED_GPIO "/sys/class/gpio/gpio60/"
#include <unistd.h>
#include <string>
#include <sstream>
using namespace std;
using namespace cgicc;

void writeGPIO(string filename, string value){
   fstream fs;
   string path(LED_GPIO);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

string read(string path, string fileName){
   fstream fs;
   fs.open((path + fileName).c_str());
   if (!fs.is_open()){
	   perror("GPIO: read failed to open file ");
    }
   string input;
   getline(fs,input);
   fs.close();
   return input;
}

int getVal(string path){
	string out = read(path, "value");
	if(out == "0"){
		return 0;
	}
	else if(out == "1"){
		return 1;
	}
}

int main(){
   Cgicc form;                      // the CGI form object
   
   string inGPIO = "46";
   ostringstream inGstream;
   //concatenate through string stream
   inGstream<<"/sys/class/gpio/gpio"<<inGPIO<<"/";
   //convert stream to string
   string inG = string(inGstream.str());
   
   // get the state of the form that was submitted - script calls itself
   bool isStatus = form.queryCheckbox("status");

   char *value = getenv("REMOTE_ADDR");    // The remote IP address
 
   // generate the form but use states that are set in the submitted form
   cout << HTTPHTMLHeader() << endl;       // Generate the HTML form
   cout << html() << head() << title("LED Example") << head() << endl;
   cout << body() << h1("CPE 422 Reading a PushButton as Digital Input") << endl;
   cout << body() << h1("Reading a PushButton on gpio46 via a Web Browser") << endl;
   cout << "<form action=\"/cgi-bin/read_button.cgi\" method=\"POST\">\n";
   cout << "<div>";
   cout << "<input type=\"submit\" value=\"Read Button\" />";
   cout << "</div></form>";
   
   cout<< "<h1>PushButton State</h1>";
   if(getVal(inG) == 0){
	   cout<< "<h1>Button is Pressed</h1>";
   }
   else if (getVal(inG) == 1){
	   cout<< "<h1>Button is not Pressed</h1>";
   }
   else{
	   cout<< "<h1>Invalid State</h1>";
   }

   cout << "<div> The CGI REMOTE_ADDR value is " << value << "</div>";
   cout << body() << html();
   return 0;
}

