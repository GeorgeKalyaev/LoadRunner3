Action()
{
	lr_start_transaction(tr_main = "MAIN_UC002_DeletingTickets_1");

	lr_start_transaction(tr_name = "UC002_DeletingTickets_1_01Login"); // логин

	Login();

	lr_end_transaction("UC002_DeletingTickets_1_01Login",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction(tr_name = "UC002_DeletingTickets_1_02Itinerary"); // переход к билетам

	status = web_url("Itinerary Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
		Check(status, tr_name);
 
	lr_end_transaction("UC002_DeletingTickets_1_02Itinerary",LR_AUTO);

	lr_think_time(3);
	
	lr_start_transaction(tr_name = "UC002_DeletingTickets_1_03Deleting"); // Удаление всех билетов
	/*web_add_cookie("SRCHUID=V=2&GUID=BAAA90DA4A15403E99F53067BF797C98&dmnchg=1; DOMAIN=edge.microsoft.com");
	web_add_cookie("SRCHD=AF=NOFORM; DOMAIN=edge.microsoft.com");
	web_add_cookie("_EDGE_V=1; DOMAIN=edge.microsoft.com");
	web_add_cookie("MUID=3F0B04987E7F60B23C010B737F1461DB; DOMAIN=edge.microsoft.com");
	web_add_cookie("SRCHUSR=DOB=20201013; DOMAIN=edge.microsoft.com");
	web_add_cookie("SRCHHPGUSR=SRCHLANGV2=ru; DOMAIN=edge.microsoft.com");*/
  
	status = web_submit_data("itinerary.pl",
		"Action=http://192.168.26.1:1080/cgi-bin/itinerary.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://192.168.26.1:1080/cgi-bin/itinerary.pl",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		//"Name=flightID", "Value={flightID_1}", ENDITEM,
		//"Name=flightID", "Value={flightID_2}", ENDITEM,
		"Name=2", "Value=on", ENDITEM,
		"Name=3", "Value=on", ENDITEM,
		"Name=removeAllFlights.x", "Value=36", ENDITEM,
		"Name=removeAllFlights.y", "Value=9", ENDITEM,
		//EXTRARES,
		//"URL=https://edge.microsoft.com/neededge/v1?bucket=29&customertype=1", ENDITEM,
		LAST);
	Check(status, tr_name);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_end_transaction("UC002_DeletingTickets_1_03Deleting",LR_AUTO);

	lr_think_time(3);

	lr_start_transaction("UC002_DeletingTickets_1_04Logout"); // Выход

	Logout();
 
	lr_end_transaction("UC002_DeletingTickets_1_04Logout",LR_AUTO);
	lr_end_transaction("MAIN_UC002_DeletingTickets_1",LR_AUTO);
	return 0;
}