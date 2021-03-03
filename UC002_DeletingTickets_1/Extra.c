Extra()
{
	return 0;
}


Check(int status, char *tr_name)
{
	if(status == LR_FAIL){
		lr_error_message("Возникла ошибка -> перелогин");
		lr_end_transaction(tr_name, LR_FAIL);
		lr_end_transaction("MAIN_UC002_DeletingTickets_1", LR_FAIL);
		Relogin();
		lr_exit(LR_EXIT_MAIN_ITERATION_AND_CONTINUE, LR_FAIL);
	}
	return 0;
}


Relogin()
{
	
	lr_start_transaction("_UC002_DeletingTickets_1_Relogin");
	
	
	lr_save_datetime("%d.%m.%Y %H:%M:%S", DATE_NOW, "currDateTime");
	lr_output_message("Relogin, time=%s, iteration=%s", lr_eval_string("{currDateTime}"), lr_eval_string("{iteration}"));
	
	Logout();
	
	lr_think_time(3); // для закрытии сессии
	
	lr_end_transaction("_UC002_DeletingTickets_1_Relogin", LR_FAIL);
	
	Login();
	
	return 0;
}


Logout()
{
	web_url("SignOff Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	
	return 0;
}

Login()
{
	web_reg_save_param_regexp(
	    "ParamName=userSession", 
	    "RegExp=name=\"userSession\" value=\"([^\"]+)\"/>",
	    "Ordinal=1",
		LAST);
	
	web_url("WebTours", 
		"URL=http://192.168.26.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

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
		"Name=login.x", "Value=38", ENDITEM, 
		"Name=login.y", "Value=5", ENDITEM, 
		LAST);
	
	return 0;
}
