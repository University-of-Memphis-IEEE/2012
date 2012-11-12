
var userid = GetCookie("USERID");
var sign = 'Sign-Off';
var signuri = '/profile/logout.cgi';

var header_mid_img = "/analogs/images/header_middle_signon_en.gif";
var header_lng_img = "/analogs/images/header_lang_select_en.gif";

var curHref = document.location.href;
var curHrefDe = curHref.split('#');

if (curHref.match("\/en\/")) {
	setCookie('lang_choosen', 'en_US')
} else if (curHref.match("\/jp\/")) {
	setCookie('lang_choosen', 'ja_JP')
} else if (curHref.match("\/cn\/")) {
	setCookie('lang_choosen', 'zh_CN')
} else if (curHref.match("\/tw\/")) {
	setCookie('lang_choosen', 'zh_TW')
} else if (curHref.match("\/kr\/")) {
	setCookie('lang_choosen', 'ko_KR')
} else if (curHref.match("\/de\/")) {
	setCookie('lang_choosen', 'de_DE')
}
curHref = curHref.replace(/lang_choosen=/gi, "entry=");
var langnavindex2 = getCookie2('lang_choosen');

if (userid) {
  var signuri = '/profile/logout.cgi';
  header_mid_img = "/analogs/images/header_middle_signoff_en.gif";
} else {
  var signuri = 'https://www.national.com/profile/login.cgi';
  var sign = 'Sign-On';
}

if (langnavindex2 == 'ja_JP') {
  if (userid) {
	header_mid_img = "/analogs/images/header_middle_signoff_jp.gif";
  } else {
	header_mid_img = "/analogs/images/header_middle_signon_jp.gif";
  }
  header_lng_img = "/analogs/images/header_lang_select_jp.gif";
} else if (langnavindex2 == 'zh_CN') {
  if (userid) {
	header_mid_img = "/analogs/images/header_middle_signoff_cn.gif";
  } else {
	header_mid_img = "/analogs/images/header_middle_signon_cn.gif";
  }
  header_lng_img = "/analogs/images/header_lang_select_cn.gif";
} else if (langnavindex2 == 'zh_TW') {
  if (userid) {
	header_mid_img = "/analogs/images/header_middle_signoff_tw.gif";
  } else {
	header_mid_img = "/analogs/images/header_middle_signon_tw.gif";
  }
  header_lng_img = "/analogs/images/header_lang_select_tw.gif";
} else if (langnavindex2 == 'ko_KR') {
  if (userid) {
	header_mid_img = "/analogs/images/header_middle_signoff_kr.gif";
  } else {
	header_mid_img = "/analogs/images/header_middle_signon_kr.gif";
  }
  header_lng_img = "/analogs/images/header_lang_select_kr.gif";
} else if (langnavindex2 == 'de_DE') {
}

function langnavActive(langnavindex) {
  langnavindex = getCookie2('lang_choosen');

  if (langnavindex == 'ja_JP') {
	  document.getElementById('langnavja_JP').className = 'langnavActive';
  } else if (langnavindex == 'zh_CN') {
	  document.getElementById('langnavzh_CN').className = 'langnavActive';
  } else if (langnavindex == 'zh_TW') {
	  document.getElementById('langnavzh_TW').className = 'langnavActive';
  } else if (langnavindex == 'ko_KR') {
	  document.getElementById('langnavko_KR').className = 'langnavActive';
  } else if (langnavindex == 'de_DE') {
	  document.getElementById('langnavde_DE').className = 'langnavActive';
  } else {
	  document.getElementById('langnaven_US').className = 'langnavActive';
  }
}
function getCookieVal (offset) {
  var endstr = document.cookie.indexOf (";", offset);
  if (endstr == -1)
	endstr = document.cookie.length;
  return unescape(document.cookie.substring(offset, endstr));
}
function GetCookie (name) {
  var arg = name + "=";
  var alen = arg.length;
  var clen = document.cookie.length;
  var i = 0;
  while (i < clen) {
	var j = i + alen;
	if (document.cookie.substring(i, j) == arg)
	  return getCookieVal (j);
	i = document.cookie.indexOf(" ", i) + 1;
	if (i == 0) break;
  }
  return null;
}
function setCookie(name, value, expires, path, domain, secure) {
	document.cookie= name + "=" + escape(value) +
		"; expires=Thu, 01-Jan-2021 00:00:01 GMT" +
		"; path=/" +
		"; domain=.national.com" +
		((secure) ? "; secure" : "");
}

function getCookie2(name) {
	var dc = document.cookie;
	var prefix = name + "=";
	var begin = dc.indexOf("; " + prefix);
	if (begin == -1) {
		begin = dc.indexOf(prefix);
		if (begin != 0) return null;
	} else {
		begin += 2;
	}
	var end = document.cookie.indexOf(";", begin);
	if (end == -1) {
		end = dc.length;
	}
	return unescape(dc.substring(begin + prefix.length, end));
}
function deleteCookie(name, path, domain) {
	if (getCookie(name)) {
		document.cookie = name + "=" +
			((path) ? "; path=" + path : "") +
			((domain) ? "; domain=" + domain : "") +
			"; expires=Thu, 01-Jan-70 00:00:01 GMT";
	}
}
function getHref() {
   return document.location.href;
}
function clear_textbox() {
  document.getElementById('HD_SearchBG').className='hd_searchbg_active';
  if (document.search_wrap.textfield.value == "Search For..")
	document.search_wrap.textfield.value = "";
}
function reset_textbox() {
  document.getElementById('HD_SearchBG').className='hd_searchbg';
  if (document.search_wrap.textfield.value == "")
	document.search_wrap.textfield.value = "Search For..";
}

//This function takes care of submitting the search form.
function jsSubmit() {
	if(document.location.href.indexOf("https") != -1)
	{
		this.document.search_wrap.action = "http://www.national.com/JS/searchDocument.do";
	}
	this.document.search_wrap.submit();
	return false;
}




