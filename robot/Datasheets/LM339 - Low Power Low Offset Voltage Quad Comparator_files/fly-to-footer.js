/************************************************************************************************************
(C) www.dhtmlgoodies.com, March 2006

This is a script from www.dhtmlgoodies.com. You will find this and a lot of other scripts at our website.	

Terms of use:
You are free to use this script as long as the copyright message is kept intact. However, you may not
redistribute, sell or repost it without our permission.

Version:
	1.0	Released	March. 3rd 2006

Thank you!

www.dhtmlgoodies.com
Alf Magne Kalleland

************************************************************************************************************/

var flyingSpeed = 5;
var url_addProductToBasket = '/analogs/javascript/addProductJSP.cgi';
//var url_listProductToBasket = '/analogs/javascript/listProduct.cgi';
var url_listProductToBasket = '/include/getUserData.jsp?type=briefcase&';
var url_removeProductFromBasket = '/analogs/javascript/removeProduct.cgi';
var url_resetMyBriefcaseCount = '/include/getUserData.jsp';
var url_listMyBriefcaseNotes = '/analogs/jsp/briefcaseNotesFrame.cgi';
var url_removeMyBriefcaseNotes = '/analogs/jsp/briefcaseNotes.cgi';
var url_updateCompare = '/analogs/javascript/updateCompareJSP.cgi';
var txt_totalPrice = 'Click any "Briefcase" icon to add an item ';
var ePP = 0;
var ePP_txt = "Actions (<a href='http://www.national.com/ENG/cgi-bin/ePitchPak/form.html?imp=bc'>Send to ePitchPak</a>)";

var shopping_cart_div = false;
var flyingDiv = false;
var currentProductDiv = false;

var shopping_cart_x = false;
var shopping_cart_y = false;

var slide_xFactor = false;
var slide_yFactor = false;

var diffX = false;
var diffY = false;

var currentXPos = false;
var currentYPos = false;

var ajaxObjects = new Array();


function shoppingCart_getTopPos(inputObj)
{		
  var returnValue = inputObj.offsetTop;
  while((inputObj = inputObj.offsetParent) != null){
  	if(inputObj.tagName!='HTML')returnValue += inputObj.offsetTop;
  }
  return returnValue;
}

function shoppingCart_getLeftPos(inputObj)
{
  var returnValue = inputObj.offsetLeft;
  while((inputObj = inputObj.offsetParent) != null){
  	if(inputObj.tagName!='HTML')returnValue += inputObj.offsetLeft;
  }
  return returnValue;
}
	

function addToBasket(productId) {
	if (!userid) { alert('You must sign-in to activate My Briefcase'); return false; }
	bringToTop('2');
	doMyBriefCase();
	if(!shopping_cart_div)shopping_cart_div = document.getElementById('shopping_cart');
	if(!flyingDiv){
		flyingDiv = document.createElement('DIV');
		flyingDiv.style.position = 'absolute';
		document.body.appendChild(flyingDiv);
	}
	
	shopping_cart_x = shoppingCart_getLeftPos(shopping_cart_div);
	shopping_cart_y = shoppingCart_getTopPos(shopping_cart_div);

	currentProductDiv = document.getElementById('slidingProduct' + productId);
	
	currentXPos = shoppingCart_getLeftPos(currentProductDiv);
	currentYPos = shoppingCart_getTopPos(currentProductDiv);
	
	diffX = shopping_cart_x - currentXPos;
	diffY = shopping_cart_y - currentYPos;
	

	
	var shoppingContentCopy = currentProductDiv.cloneNode(true);
	shoppingContentCopy.id='';
	flyingDiv.innerHTML = '';
	flyingDiv.style.left = currentXPos + 'px';
	flyingDiv.style.top = currentYPos + 'px';
	flyingDiv.appendChild(shoppingContentCopy);
	flyingDiv.style.display='block';
	flyingDiv.style.width = currentProductDiv.offsetWidth + 'px';
	flyToBasket(productId);
	
}


function flyToBasket(productId)
{
	var maxDiff = Math.max(Math.abs(diffX),Math.abs(diffY));
	var moveX = (diffX / maxDiff) * flyingSpeed;;
	var moveY = (diffY / maxDiff) * flyingSpeed;	
	
	currentXPos = currentXPos + moveX;
	currentYPos = currentYPos + moveY;
	
	flyingDiv.style.left = Math.round(currentXPos) + 'px';
	flyingDiv.style.top = Math.round(currentYPos) + 'px';	
	
	
	if(moveX>0 && currentXPos > shopping_cart_x){
		flyingDiv.style.display='none';		
	}
	if(moveX<0 && currentXPos < shopping_cart_x){
		flyingDiv.style.display='none';		
	}
		
	if(flyingDiv.style.display=='block')setTimeout('flyToBasket("' + productId + '")',10); else ajaxAddProduct(productId);	
}


function showAjaxBasketContentCGI(ajaxIndex) {
        // Getting a reference to the shopping cart items table
        var itemBox = document.getElementById('shopping_cart_items');
        
        var productItems = ajaxObjects[ajaxIndex].response.split('|||');        // Breaking response from Ajax into tokens
        
        if(document.getElementById('shopping_cart_items_product' + productItems[0])){
                // A product with this id is allready in the basket - just add number items
                var row = document.getElementById('shopping_cart_items_product' + productItems[0]);
                //var items = row.cells[0].innerHTML /1;
                //items = items + 1;
                //row.cells[0].innerHTML = items;
        }else{  // Product isn't allready in the basket - add a new row
                var tr = itemBox.insertRow(-1);
                tr.id = 'shopping_cart_items_product' + productItems[0]
                
                var td = tr.insertCell(-1);
                td.innerHTML = productItems[1];         // Item
                
                var td = tr.insertCell(-1);
                td.innerHTML = productItems[2];         // Info
                
                var td = tr.insertCell(-1);
                var a = document.createElement('A');
                td.appendChild(a);
                a.name = '#';
                a.onclick = function(){ removeProductFromBasket(productItems[0]); };
                var img = document.createElement('IMG');
                img.src = 'http://www.national.com/analogs/images/remove.gif';
                img.alt = 'Remove ' + productItems[1] + ' from My Briefcase';
                a.appendChild(img);
                //td.innerHTML = '<a href="#" onclick="removeProductFromBasket("' + productItems[0] + '");return false;">
                //<img src="images/remove.gif"></a>';
        }
        
        
        updateTotalPrice();
        //removeAllProductsFromBasket(productItems[0]);
        //ajaxListProduct(productItems[0]);
        ajaxResetCount();
        ajaxObjects[ajaxIndex] = false;
                
}


function showAjaxBasketContent(ajaxIndex) {
	// Getting a reference to the shopping cart items table
	var itemBox = document.getElementById('shopping_cart_items');
	var productLineItems = ajaxObjects[ajaxIndex].response.split('\n');
     for(var no=0;no<productLineItems.length;no++) {	
	var productItems = productLineItems[no].split('|||'); // Breaking response from Ajax into tokens
       if(productItems[0].indexOf(":::") > 3){
        var FMD = productItems[6].split(' ');
	if(document.getElementById('shopping_cart_items_product' + productItems[0])){	
		// A product with this id is allready in the basket - just add number items
		var row = document.getElementById('shopping_cart_items_product' + productItems[0]);
		//var items = row.cells[0].innerHTML /1;
		//items = items + 1;
		//row.cells[0].innerHTML = items;
	}else{	// Product isn't allready in the basket - add a new row
		var tr = itemBox.insertRow(-1);
		tr.id = 'shopping_cart_items_product' + productItems[0]
		
		var td = tr.insertCell(-1);
		td.setAttribute("align","left");
		//td.innerHTML = productItems[1]; 	// Item
                td.innerHTML = '<a href="http://www.national.com/JS/searchDocument.do?textfield='+productItems[1]+'" onMouseOver="ajax_showTooltip(\''+productItems[5]+'\',this);return false" onmouseout="ajax_hideTooltip()">'+productItems[1]+'</a>';

		var td = tr.insertCell(-1);
		td.setAttribute("align","left");
		td.innerHTML = productItems[2]; 	// ProductLine

		var td = tr.insertCell(-1);
                td.setAttribute("align","left");
                td.innerHTML = productItems[6];         // FMD

                var td = tr.insertCell(-1);
		td.setAttribute("align","left");
                td.innerHTML = productItems[3];         // Actions

		var td = tr.insertCell(-1);
                //td.innerHTML = "<input type=checkbox name='comp"+productItems[1]+"' value='"+productItems[1]+"' onclick=\"updateAjaxCompare('" + productItems[0] + "');\">"; //Compare	
                td.innerHTML = "<input type=checkbox name='compare' value='"+productItems[1]+"' onclick=\"updateAjaxCompare('" + productItems[0] + "');\">"; //Compare	

		var td = tr.insertCell(-1);
		var a = document.createElement('A');
		td.appendChild(a);
		a.name = '#';
		a.onclick = function(){ removeProductFromBasket(productItems[0]); };
		var img = document.createElement('IMG');
		img.src = 'http://www.national.com/analogs/images/remove.gif';
		img.alt = 'Remove ' + productItems[1] + ' from My Briefcase';
		a.appendChild(img);
		//td.innerHTML = '<a href="#" onclick="removeProductFromBasket("' + productItems[0] + '");return false;">
		//<img src="images/remove.gif"></a>';	
	} 
       }
      }
	updateTotalPrice();
        //removeAllProductsFromBasket(productItems[0]);
        //ajaxListProduct(productItems[0]);	
	ajaxResetCount();
	ajaxObjects[ajaxIndex] = false;		
	
}


function listAjaxBasketContent(ajaxIndex) {
  // Getting a reference to the shopping cart items table
  var itemBox = document.getElementById('shopping_cart_items');
  var productLineItems = ajaxObjects[ajaxIndex].response.split('\n');
  var prev_ProductLine = '';
  var prev_GroupName = '';
  for(var no=0;no<productLineItems.length;no++){
        var productItems = productLineItems[no].split('|||');        // Breaking response from Ajax into tokens
        if(productItems[0].length > 3){
		var FMD = productItems[6].split(' ');
                ePP = productItems[3].indexOf("ePitchPak");
                var tr = itemBox.insertRow(-1);
                tr.id = 'shopping_cart_items_product' + productItems[0] // ID
                var td = tr.insertCell(-1);
		td.setAttribute("align","left");
                td.innerHTML = '<a href="http://www.national.com/JS/searchDocument.do?textfield='+productItems[1]+'" onMouseOver="ajax_showTooltip(\''+productItems[5]+'\',this);return false" onmouseout="ajax_hideTooltip()">'+productItems[1]+'</a>';
                var td = tr.insertCell(-1);
		td.setAttribute("align","left");
                td.innerHTML = productItems[2];         // Product Line

		var td = tr.insertCell(-1);
                td.setAttribute("align","left");
                td.innerHTML = FMD[0];         // FMD 

                var td = tr.insertCell(-1);
		td.setAttribute("align","left");
		td.innerHTML = productItems[3];         // Links ePP
		var td = tr.insertCell(-1);

		//td.innerHTML = "<input type=checkbox name='comp"+productItems[1]+"' value='"+productItems[1]+"' onclick=\"updateAjaxCompare('" + productItems[0] + "');\" " + productItems[4] + ">"; //Compare
		td.innerHTML = "<input type=checkbox name='compare' value='"+productItems[1]+"' onclick=\"updateAjaxCompare('" + productItems[0] + "');\" " + productItems[4] + ">"; //Compare

                var td = tr.insertCell(-1);
                td.innerHTML = "<a name='#' onclick=removeProductFromBasket('" + productItems[0] + "')><img src='http://www.national.com/analogs/images/remove.gif' alt='Remove " + productItems[1] + " from My Briefcase'></a>";
        }


        updateTotalPrice();
        ajaxObjects[ajaxIndex] = false;
  } //forloop
 

}

function listAjaxMyBriefcaseNotes(ajaxIndex) {
  var itemBox = document.getElementById('myBriefcaseNotesArea');
  itemBox.innerHTML = ajaxObjects[ajaxIndex].response;
}
function ajaxListMyBriefcaseNotes(productId) {
        var ajaxIndex = ajaxObjects.length;
        ajaxObjects[ajaxIndex] = new sack();
        ajaxObjects[ajaxIndex].requestFile = url_listMyBriefcaseNotes; 
        ajaxObjects[ajaxIndex].setVar('productId',productId);
        ajaxObjects[ajaxIndex].onCompletion = function(){ listAjaxMyBriefcaseNotes(ajaxIndex); };
        ajaxObjects[ajaxIndex].runAJAX();               // Execute AJAX function
}
function removeNote(recipientId) {
  var recipientRow = document.getElementById(recipientId);
  recipientRow.parentNode.removeChild(recipientRow);
}
function ajaxRemoveMyBriefcaseNotes(productId,removeId) {
        var ajaxIndex = ajaxObjects.length;
        ajaxObjects[ajaxIndex] = new sack();
        ajaxObjects[ajaxIndex].requestFile = url_removeMyBriefcaseNotes;
        ajaxObjects[ajaxIndex].setVar('removeId',removeId);
        ajaxObjects[ajaxIndex].onCompletion = function(){ removeNote(productId); };
        ajaxObjects[ajaxIndex].runAJAX();               // Execute AJAX function
}


function listAjaxBasketContentCGI(ajaxIndex)
{
  // Getting a reference to the shopping cart items table
  var itemBox = document.getElementById('shopping_cart_items');
  var productLineItems = ajaxObjects[ajaxIndex].response.split('\n');
  var prev_ProductLine = '';
  var prev_GroupName = '';
  for(var no=0;no<productLineItems.length;no++){      
        var productItems = productLineItems[no].split('|||');        // Breaking response from Ajax into tokens
                
        if(productItems[0].length > 3){  
		var temp_store = productItems[0];
	      if (productItems[5] != "" && prev_GroupName != productItems[5]) {
		var tr = itemBox.insertRow(-1);
                tr.id = 'shopping_cart_items_productGroup' + productItems[5]
                
                var td = tr.insertCell(-1);
                td.setAttribute("colspan", "2");
                td.innerHTML = '<BR><BR><center><font color=red><B>' + productItems[5] + '</B></font></center>';
                var td = tr.insertCell(-1);
                td.innerHTML = '';
	      }
		prev_GroupName = productItems[5];
	      if (prev_ProductLine != productItems[3]) {
		var tr = itemBox.insertRow(-1);
		tr.id = 'shopping_cart_items_productGroup' + productItems[3]

		var td = tr.insertCell(-1);
		td.setAttribute("colspan", "2");
		td.innerHTML = '<B>' + productItems[3] + '</B>';
		//var td = tr.insertCell(-1);
                //td.innerHTML = ''; 
		var td = tr.insertCell(-1);
                td.innerHTML = '';  
	      }
		prev_ProductLine = productItems[3];

		ePP = productItems[2].indexOf("ePitchPak");

                var tr = itemBox.insertRow(-1);
                tr.id = 'shopping_cart_items_product' + productItems[0]

                var td = tr.insertCell(-1);
                td.innerHTML = '- ' + productItems[1];         // Item
        
                var td = tr.insertCell(-1);
                td.innerHTML = productItems[2];         // Info
        
                var td = tr.insertCell(-1);

                //var a = document.createElement('A');
                //td.appendChild(a);
                //a.name = '#';
		//a.onclick = function(){ alert('William1: ' + temp_store); };
                //a.onclick = function(){ removeProductFromBasket(temp_store); };
                //var img = document.createElement('IMG');
                //img.src = 'http://www.national.com/analogs/images/remove.gif';
                //img.alt = 'Remove ' + productItems[1] + ' from My Briefcase';
                //a.appendChild(img);

                td.innerHTML = "<a name='#' onclick=removeProductFromBasket('" + productItems[0] + "')><img src='http://www.national.com/analogs/images/remove.gif' alt='Remove " + productItems[4] + " from My Briefcase'></a>";
        }

        
        updateTotalPrice();
        ajaxObjects[ajaxIndex] = false;
  } //forloop
  
        
}

function updateTotalPrice()
{
	var itemBox = document.getElementById('shopping_cart_items');
	// Calculating total price and showing it below the table with basket items
	var totalPrice = 0;
	if(document.getElementById('shopping_cart_totalprice')){
		for(var no=1;no<itemBox.rows.length;no++){
		  //totalPrice = totalPrice + (itemBox.rows[no].cells[0].innerHTML.replace(/[^0-9]/g) * itemBox.rows[no].cells[2].innerHTML);
		  totalPrice = totalPrice + 1;	
		  //ePP = itemBox.rows[no].cells[0].innerHTML.indexOf("ePitchPak");
		}		
		//document.getElementById('shopping_cart_totalprice').innerHTML = txt_totalPrice + totalPrice.toFixed(2);
		//document.getElementById('shopping_cart_totalprice').innerHTML = txt_totalPrice + totalPrice.toFixed(0);
		if (totalPrice < 1) {
		  document.getElementById('shopping_cart_totalprice').innerHTML = txt_totalPrice;
		} else if (ePP > 0) {
		  document.getElementById('shopping_cart_totalprice').innerHTML = ePP_txt;
		} else {
		  document.getElementById('shopping_cart_totalprice').innerHTML = "Actions";
		}
		//document.getElementById('shopping_cart_totalprice').innerHTML = txt_totalPrice + totalPrice.toFixed(0) + ePP_txt + ePP;
	}	
	//if(document.getElementById('cntBriefcaseItems')){
	  document.getElementById('cntBriefcaseItems').innerHTML = "My Briefcase (" + totalPrice + ")";
	//}
}


function getelementsbyPrefix(inPrefix,inRoot){ 
  var elem_array = new Array; 
  if(typeof inRoot.firstChild!= 'undefined'){ 
    var elem = inRoot.firstChild; 
    while (elem!= null){ 
      if(typeof elem.firstChild!= 'undefined'){ 
        elem_array = elem_array.concat(getelementsbyPrefix(inPrefix,elem)); 
      } 
      if(typeof elem.id!= 'undefined'){ 
        var reg = new RegExp ( '^'+inPrefix+'.*' ); 
        if(elem.id.match(reg)){ 
          elem_array.push(elem); 
        } 
      } 
      elem = elem.nextSibling; 
    } 
  } 
  return elem_array; 
} 

function Displayelements(in_elem_array){ 
  if(in_elem_array.length){ 
    for(var c=0; c<in_elem_array.length; c++){ 
      //alert(in_elem_array[c].id); 
      var productRow = document.getElementById(in_elem_array[c].id);
      productRow.parentNode.removeChild(productRow);
    } 
  } 
} 

function removeAllProductsFromBasket(productId) {
  Displayelements(getelementsbyPrefix('shopping_cart_items_product',document.documentElement)); 
}

function removeProductFromBasket(productId)
{ 
    if (productId != "removeAll") {
	var productRow = document.getElementById('shopping_cart_items_product' + productId);
	
	var numberOfItemCell = productRow.cells[0];
	if(numberOfItemCell.innerHTML == '1'){
		productRow.parentNode.removeChild(productRow);	
	}else{
		//numberOfItemCell.innerHTML = numberOfItemCell.innerHTML/1 - 1;
		productRow.parentNode.removeChild(productRow);
	}
    }
	updateTotalPrice();
	ajaxRemoveProduct(productId);
	ajaxResetCount();
	//removeAllProductsFromBasket(productId);
	//ajaxListProduct(productId);	
}

function ajaxValidateRemovedProduct(ajaxIndex)
{
	if(ajaxObjects[ajaxIndex].response!='OK')alert('Error while removing product from the database');
	//ajaxResetCount();	
}

function ajaxRemoveProduct(productId)
{
	var ajaxIndex = ajaxObjects.length;
	ajaxObjects[ajaxIndex] = new sack();
	ajaxObjects[ajaxIndex].requestFile = url_removeProductFromBasket;	// Saving product in this file
	ajaxObjects[ajaxIndex].setVar('productIdToRemove',productId);
	ajaxObjects[ajaxIndex].onCompletion = function(){ ajaxValidateRemovedProduct(ajaxIndex); };	//Specify function that will be executed after file has been found
	ajaxObjects[ajaxIndex].runAJAX();		// Execute AJAX function		
}

function ajaxAddProduct(productId)
{
	var ajaxIndex = ajaxObjects.length;
	ajaxObjects[ajaxIndex] = new sack();
	ajaxObjects[ajaxIndex].requestFile = url_addProductToBasket;	// Saving product in this file
	ajaxObjects[ajaxIndex].setVar('productId',productId);
	ajaxObjects[ajaxIndex].onCompletion = function(){ showAjaxBasketContent(ajaxIndex); }; //Specify function that will be executed after file has been found
	ajaxObjects[ajaxIndex].runAJAX();		// Execute AJAX function		
	
}

function ajaxListProduct(productId)
{
        var ajaxIndex = ajaxObjects.length;
        ajaxObjects[ajaxIndex] = new sack();
        ajaxObjects[ajaxIndex].requestFile = url_listProductToBasket;    // Saving product in this file
        ajaxObjects[ajaxIndex].setVar('productId',productId);
        ajaxObjects[ajaxIndex].onCompletion = function(){ listAjaxBasketContent(ajaxIndex); };
        ajaxObjects[ajaxIndex].runAJAX();               // Execute AJAX function
}

function ajaxResetCount(productId) {
        var ajaxIndex = ajaxObjects.length;
        ajaxObjects[ajaxIndex] = new sack();
        ajaxObjects[ajaxIndex].requestFile = url_resetMyBriefcaseCount;       // Saving product in this file
        ajaxObjects[ajaxIndex].setVar('reset','1');
        ajaxObjects[ajaxIndex].onCompletion = function(){ delete_Cookie('footer','/',''); };     // Specify function
        ajaxObjects[ajaxIndex].runAJAX();               // Execute AJAX function
}

function updateAjaxCompare(productId) {
  var ajaxIndex = ajaxObjects.length;
  ajaxObjects[ajaxIndex] = new sack();  
  ajaxObjects[ajaxIndex].requestFile = url_updateCompare;    // Saving product in this file
  ajaxObjects[ajaxIndex].setVar('productId',productId);
  ajaxObjects[ajaxIndex].onCompletion = function(){ ajaxResetCount(productId); };
  ajaxObjects[ajaxIndex].runAJAX();               // Execute AJAX function
}
