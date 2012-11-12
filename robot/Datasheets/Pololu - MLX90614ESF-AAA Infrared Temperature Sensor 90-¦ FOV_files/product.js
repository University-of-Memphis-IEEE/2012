function productInit(path)
{
    updatePictureScroll();

    restoreScrollPosition(path);
}

function restoreScrollPosition(path)
{
    // do not scroll if the user has already scrolled (that would be annoying!)
    var current_y = (document.all)?document.body.scrollTop:window.pageYOffset;
    if(current_y != 0)
	return;

    pos=document.cookie.indexOf("scroll=");
    if (pos==-1)
	return; // no cookie found
    pos += 7; // go to the beginning of the value
    end = document.cookie.indexOf(";", pos);
    if (end==-1)
	end=document.cookie.length; // it is the last cookie
    
    window.scrollTo(0,document.cookie.substring(pos,end));

    // clear the cookie so reloading will work
    var date = new Date();
    date.setTime(date.getTime()-24*60*60*1000); // date in the past
    var cookie = "scroll=; expires="+date.toGMTString()+"; path=";

    if(/MSIE (\d+\.\d+);/.test(navigator.userAgent))
	cookie += "/"; // IE does not respect the last element of the path
    else
	cookie += path;
    document.cookie = cookie;
}

function saveScrollPosition(path)
{
    var y = (document.all)?document.body.scrollTop:window.pageYOffset;
    if(y == 0)
	y = document.documentElement.scrollTop; // make IE work

    var date = new Date();
    date.setTime(date.getTime()+30*1000);

    var cookie = "scroll="+y+"; expires="+date.toGMTString()+"; path=";
    if(/MSIE (\d+\.\d+);/.test(navigator.userAgent))
	cookie += "/"; // IE does not respect the last element of the path
    else
	cookie += path;
    document.cookie = cookie;
}

function updatePictureScroll()
{
    var left = document.getElementById("other_pictures_scroll_left_a");
    var right = document.getElementById("other_pictures_scroll_right_a");
    var pictures = document.getElementById("other_pictures");
    var p = document.getElementById("other_pictures_table");

    if(pictures.offsetWidth < p.offsetWidth)
    {
	left.style.display = "block";
	right.style.display = "block";
    }
    else
    {
	left.style.display = "none";
	right.style.display = "none";
    }

    if(p.style.marginLeft == "0px")
    {
	left.style.display = "none";
    }
    if(parseInt(p.style.marginLeft) + p.offsetWidth <= pictures.offsetWidth + 3)
    {
	right.style.display = "none";
    }
}

function picturesScrollLeft()
{
    var p = document.getElementById("other_pictures_table");
    p.style.marginLeft = (parseInt(p.style.marginLeft) + (50+2+3)*4) + "px"; // 223 should match the width of the div
    updatePictureScroll();
    return false; // so that the link will not be followed
}

function picturesScrollRight()
{
    var p = document.getElementById("other_pictures_table");
    p.style.marginLeft = (parseInt(p.style.marginLeft) - (50+2+3)*4) + "px";
    updatePictureScroll();
    return false; // so that the link will not be followed
}

function pictureView(imgurl, link)
{
    var main_picture_img = document.getElementById("main_picture_img");
    var main_picture_a = main_picture_img.parentNode;

    main_picture_img.src = imgurl;
    main_picture_img.alt = "";
    main_picture_a.href = link;
    
    return false;
}