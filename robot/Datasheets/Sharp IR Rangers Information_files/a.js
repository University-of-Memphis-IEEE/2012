function navOver(o) {
 o.style.backgroundColor="#606060";
}

function navOff(o) {
 o.style.backgroundColor="#000000";
}

function showPDF(title,url) {
 if (url!="") {
   if (confirm("The PDF page generation on our website is developmental.  The formatting is likely to change as we finalize this feature.  Feel free to take a look while we work.")) {
   agent = navigator.userAgent;
   params = "";
   if (typeof(win) == "object" && !win.closed){
     win.close();
   }
   win = window.open(url,title,params);
   if (agent.indexOf("Mozilla/2") != -1 && agent.indexOf("Win") == -1) {
     win = window.open(url,title,params);
   }
   if (!win.opener) {
     win.opener = window;
   }	
   win.focus();
  }
 } else {
  alert("We are adding PDF versions of most of our website pages but this page has not been updated yet.  Please check back in the future for this feature.");
 }
}
