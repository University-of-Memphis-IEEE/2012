/************************************************************************************************************
Ajax dynamic list
Copyright (C) September 2005  DTHMLGoodies.com, Alf Magne Kalleland

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Dhtmlgoodies.com., hereby disclaims all copyright interest in this script
written by Alf Magne Kalleland.

Alf Magne Kalleland, 2006
Owner of DHTMLgoodies.com
	
************************************************************************************************************/	
function showToolTip(text){
        var xTip = 0;
        if (self.innerHeight)
        {
                xTip = self.innerWidth;
        }
        else if (document.documentElement && document.documentElement.clientHeight)
        {
                xTip = document.documentElement.clientWidth;
        }
        else if (document.body)
        {
                xTip = document.body.clientWidth;
        }
	//if(document.all)e = event;
	//if (!e) var e = window.event;
	var obj = document.getElementById('bubble_tooltip');
	var obj2 = document.getElementById('bubble_tooltip_content');
	obj2.innerHTML = text;
	obj.style.display = 'block';
	var st = Math.max(document.body.scrollTop,document.documentElement.scrollTop);
	var sl = Math.max(document.body.scrollLeft,document.documentElement.scrollLeft);
	var bodyWidth = document.body.clientWidth;
	st = 0;
	if(navigator.userAgent.toLowerCase().indexOf('safari')>=0)st=0; 
	//var leftPos = e.clientX - 100;
	//if(leftPos<0)leftPos = 0;
	//leftPos = 858;
        //var topPos = -735 + st;
	leftPos = 600;
        var topPos = 340 + st;
	if(navigator.userAgent.toLowerCase().indexOf('msie')>=0) {
		leftPos=600;
		topPos=340;
	} 
	if (xTip > 1000) {
	  leftPos = leftPos + ((xTip - 1025) / 2);
	}
	obj.style.left = leftPos + 'px';
	//obj.style.top = e.clientY - obj.offsetHeight -1 + st + 'px';
	obj.style.top = topPos + 'px'; 
	//alert("x=" + e.clientX + "," + e.offsetX + "  y=" + e.clientY + "," + e.offsetY);
 	//alert("st=" + st + " sl=" + sl + "  leftPos=" + leftPos + "  clientWidth=" + bodyWidth);
	//alert("xTipx = " + xTip + "  leftPos = " + leftPos);
}	

function hideToolTip()
{
	document.getElementById('bubble_tooltip').style.display = 'none';
	
}

function showToolTip2(e,text){
        if(document.all)e = event;

        var obj = document.getElementById('bubble_tooltip');
        var obj2 = document.getElementById('bubble_tooltip_content');
        obj2.innerHTML = text;
        obj.style.display = 'block';
        var st = Math.max(document.body.scrollTop,document.documentElement.scrollTop);
        if(navigator.userAgent.toLowerCase().indexOf('safari')>=0)st=0;
        var leftPos = e.clientX - 100;
        if(leftPos<0)leftPos = 0;
        obj.style.left = leftPos + 'px';
        obj.style.top = e.clientY - obj.offsetHeight -1 + st + 'px';
}
