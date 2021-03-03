Action()
{
	lr_start_transaction(tr_main = "MAIN_UC003_RegistrationUser_1");

	lr_start_transaction(tr_name = "UC003_RegistrationUser_1_01OpenSite");

	status = web_url("WebTours", 
		"URL=http://192.168.26.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	Check(status, tr_name);

	lr_end_transaction("UC003_RegistrationUser_1_01OpenSite",LR_AUTO);

	lr_think_time(3);
	
	lr_start_transaction(tr_name = "UC003_RegistrationUser_1_02SignUpNow");

	status = web_url("sign up now", 
		"URL=http://192.168.26.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);
	Check(status, tr_name);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_end_transaction("UC003_RegistrationUser_1_02SignUpNow",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction(tr_name = "UC003_RegistrationUser_1_03FillformContinue");

	status = web_submit_data("login.pl", 
		"Action=http://192.168.26.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={rnd}", ENDITEM, 
		"Name=password", "Value={rnd}", ENDITEM, 
		"Name=passwordConfirm", "Value={rnd}", ENDITEM, 
		"Name=firstName", "Value=", ENDITEM, 
		"Name=lastName", "Value=", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=register.x", "Value=61", ENDITEM, 
		"Name=register.y", "Value=3", ENDITEM, 
		LAST);
	Check(status, tr_name);

	lr_end_transaction("UC003_RegistrationUser_1_03FillformContinue",LR_AUTO);
	
	lr_end_transaction("MAIN_UC003_RegistrationUser_1",LR_AUTO);

	return 0;
}