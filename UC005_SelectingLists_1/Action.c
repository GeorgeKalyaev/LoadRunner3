Action()
{

	lr_start_transaction("MAIN_SelectingList_1");
	
	web_reg_save_param_regexp(
	    "ParamName=userSession", 
	    "RegExp=name=\"userSession\" value=\"([^\"]+)\"/>",
	    "Ordinal=1",
		LAST);

	lr_start_transaction("OpenSite");
	
	web_reg_find("Text=Welcome to the Web Tours site.", LAST);
	
	web_url("WebTours", 
		"URL=http://192.168.26.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("OpenSite",LR_AUTO);
	
	lr_think_time(3);
	
	lr_start_transaction("Login");
	
	web_reg_find("Text=Welcome, <b>{UserName}</b>, to the Web Tours reservation pages.", LAST);

	web_submit_data("login.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={userSession}", ENDITEM, 
		"Name=username", "Value={UserName}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=59", ENDITEM, 
		"Name=login.y", "Value=11", ENDITEM, 
		LAST);
  
	lr_end_transaction("Login",LR_AUTO);

	lr_think_time(3);
	 
	lr_start_transaction("Click_Flights");
	
	web_reg_find("Text=Web Tours Navigation Bar", LAST);

	web_url("Search Flights Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Click_Flights",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("Click_Itinerary");
	
	web_reg_find("Text=User wants the intineraries.", LAST);

	web_url("Itinerary Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_end_transaction("Click_Itinerary",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("Click_Home");
	
	web_reg_find("Text=Welcome to Web Tours", LAST);

	web_url("Home Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Click_Home",LR_AUTO);

	lr_think_time(3);
	
	lr_start_transaction("Logout");
	
	web_reg_find("Text=Web Tours", LAST);

	web_url("SignOff Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("MAIN_SelectingList_1",LR_AUTO);

	return 0;
}