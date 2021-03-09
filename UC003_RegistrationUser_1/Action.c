Action()
{
	lr_start_transaction(tr_main = "03_MAIN_RegistrationUser");

	lr_start_transaction(tr_name = "OpenSite");
	
	web_reg_find("Text=Welcome to the Web Tours site.", LAST);

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

	lr_end_transaction("OpenSite",LR_AUTO);

	lr_think_time(3);
	
	lr_start_transaction(tr_name = "Click_SignUpNow");

	web_reg_find("Text=First time registering? Please complete the form below.", LAST);
	
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

	lr_end_transaction("Click_SignUpNow",LR_AUTO);

	lr_think_time(3); 

	lr_start_transaction(tr_name = "Fillform_RegistrationUser");
	
	web_reg_find("Text=Thank you, <b>{rnd}</b>, for registering and welcome to the Web Tours family.", LAST);

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

	lr_end_transaction("Fillform_RegistrationUser",LR_AUTO);
	
	lr_end_transaction("03_MAIN_RegistrationUser",LR_AUTO);

	return 0;
}