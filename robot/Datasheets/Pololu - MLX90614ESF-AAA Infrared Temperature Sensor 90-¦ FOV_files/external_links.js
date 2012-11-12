function popup()
{
  window.open(this.href);
  return false;
}

function externalLinksNewWindow()
{
  if(!document.getElementsByTagName) return;
  var a = document.getElementsByTagName("a");
  var host = document.domain;
  var i=0;
  for(i=0;i<a.length;i++)
  {
    if(a[i].href && ((a[i].href.substr(0,7) == "http://" && a[i].href.substr(7,host.length) != host) ||
	 (a[i].href.substr(0,8) == "https://" && a[i].href.substr(8,host.length) != host)))
      a[i].onclick = popup;
  }
}
