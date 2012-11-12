/***********************************************************************
*
* getCartItem		-	Gets the Actinic Cart Value & No of Items
*
* Input: nIndex	-	Cart item index to retrieve
*							1 = TOTAL_VALUE
*							3 = CART_COUNT
*
* Returns:				Requested cart item or 0 (zero) if not found
*
************************************************************************/

//CART_CONTENT = Cookie name
//1 = TOTAL_VALUE
//3 = CART_COUNT

var PASSWORD_MATCH_ERROR = "Passwords do not match.";

function getCartItem(nIndex)
	{
	var act_cart= getCookie("CART_CONTENT")
	var sTemp =(act_cart != null) ? sTemp=act_cart.split("\t"):0;
	return (sTemp.length > 0) ? sTemp[nIndex] : 0;
	}

/***********************************************************************
*
* GotoAnchor - JS for jumping to an anchor - some user agents don't handle
*				anchors correctly if BASE HREF is present
*
* Input: 				sAnchor
*
* Returns:				nothing
*
************************************************************************/

function GotoAnchor(sAnchor)
	{
	window.location.hash = sAnchor;
	}

// The following block implements the string.parseJSON method
(function (s) {
  // This prototype has been released into the Public Domain, 2007-03-20
  // Original Authorship: Douglas Crockford
  // Originating Website: http://www.JSON.org
  // Originating URL    : http://www.JSON.org/JSON.js

  // Augment String.prototype. We do this in an immediate anonymous function to
  // avoid defining global variables.

  // m is a table of character substitutions.

  var m = {
    '\b': '\\b',
    '\t': '\\t',
    '\n': '\\n',
    '\f': '\\f',
    '\r': '\\r',
    '"' : '\\"',
    '\\': '\\\\'
  };

  s.parseJSON = function (filter) {

    // Parsing happens in three stages. In the first stage, we run the text against
    // a regular expression which looks for non-JSON characters. We are especially
    // concerned with '()' and 'new' because they can cause invocation, and '='
    // because it can cause mutation. But just to be safe, we will reject all
    // unexpected characters.

    try {
      if (/^("(\\.|[^"\\\n\r])*?"|[,:{}\[\]0-9.\-+Eaeflnr-u \n\r\t])+?$/.
        test(this)) {

          // In the second stage we use the eval function to compile the text into a
          // JavaScript structure. The '{' operator is subject to a syntactic ambiguity
          // in JavaScript: it can begin a block or an object literal. We wrap the text
          // in parens to eliminate the ambiguity.

          var j = eval('(' + this + ')');

          // In the optional third stage, we recursively walk the new structure, passing
          // each name/value pair to a filter function for possible transformation.

          if (typeof filter === 'function') {

            function walk(k, v) {
              if (v && typeof v === 'object') {
                for (var i in v) {
                  if (v.hasOwnProperty(i)) {
                    v[i] = walk(i, v[i]);
                  }
                }
              }
              return filter(k, v);
            }

            j = walk('', j);
          }
          return j;
        }
      } catch (e) {

      // Fall through if the regexp test fails.

      }
      throw new SyntaxError("parseJSON");
    };
  }
) (String.prototype);
// End public domain parseJSON block


/***********************************************************************
*
* ajaxObject - ajax communication library
*
* Input: 		url 				- the url of the json provider
*			callbackFunction 	- what function to call after communication
*
* Returns:				nothing
*
************************************************************************/

function ajaxObject(url, callbackFunction) 
	{
	var that=this;      
	this.updating = false;
	this.abort = function() 
		{
		if (that.updating) 
			{
	      that.updating=false;
	      that.AJAX.abort();
	      that.AJAX=null;
			}
		}
	this.update = function(passData,postMethod) 
		{ 
	   if (that.updating) { return false; }
	   that.AJAX = null;                          
	   if (window.XMLHttpRequest) 
			{
	      that.AJAX=new XMLHttpRequest();              
			} 
		else 
			{                                  
	      that.AJAX=new ActiveXObject("Microsoft.XMLHTTP");
			}                                             
	   if (that.AJAX==null) 
			{
	      return false;                               
			} 
		else 
			{
	      that.AJAX.onreadystatechange = function() 
				{  
				if (that.AJAX.readyState==4) 
					{             
					that.updating=false;                
					that.callback(that.AJAX.responseText,that.AJAX.status,that.AJAX.responseXML);        
					that.AJAX=null;                                         
					}                                                      
				}                                                        
	      that.updating = new Date();                              
	      if (/post/i.test(postMethod)) 
				{
				var uri=urlCall+'?'+that.updating.getTime();
				that.AJAX.open("POST", uri, true);
				that.AJAX.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
				that.AJAX.setRequestHeader("Content-Length", passData.length);
				that.AJAX.send(passData);
				} 
			else 
				{
				var uri=urlCall+'?'+passData+'&timestamp='+(that.updating.getTime()); 
				that.AJAX.open("GET", uri, true);                             
				that.AJAX.send(null);                                         
				}              
	      return true;                                             
			}                                                                           
		}
		var urlCall = url;        
		this.callback = callbackFunction || function () { };
	}
	
/***********************************************************************
*
* getStockNodes - Get the nodes of the DOM tree where nodes are used to  
*		dynamic stock display. These tags are marked with "ActinicRTS" class
*		
* Output: array of elements matching the above criteria
*
************************************************************************/

function getStockNodes()
	{
	var arrOut = new Array();	
	
	if (document.evaluate)
		{
		var xpathString = "//*[@class='ActinicRTS']"
		var xpathResult = document.evaluate(xpathString, document, null, 0, null);
		while ((arrOut[arrOut.length] = xpathResult.iterateNext())) { }
		arrOut.pop();
		}
	else if (document.getElementsByTagName)
		{
		var aEl = document.getElementsByTagName( '*' );	
		for(var i=0,j=aEl.length;i<j;i+=1)
			{
			if (aEl[i].className == 'ActinicRTS' )
				{
				arrOut.push(aEl[i]);
				};
			};			
		};	
	return arrOut;
	}

/***********************************************************************
*
* getProductStock - Gets the stock for a single product
*
* Input:	sURL	- the ajax script URL to call
*		sProdRef - product reference
*		sStock	- stock level (used for preview)
*		sShopID	- the shop ID (only used in host mode)
*
************************************************************************/

function getProductStock(sURL, sProdRef, sStock, sShopID)
	{
	return getStock(sURL, null, sProdRef, sStock, sShopID);
	}

/***********************************************************************
*
* getSectionStock - Gets the stock for products in a section
*
* Input:	sURL - the ajax script URL to call
*		sSID - the section ID list to be passed in to the ajax script
*		sProdRefs - list of the products with stock monitoring on in this section
*		sStockList - the stock level of the products in the list above
*		sShopID - the shop ID (only used in host mode)
*
************************************************************************/

function getSectionStock(sURL, sSID, sProdRefs, sStockList, sShopID)
	{
	return getStock(sURL, sSID, sProdRefs, sStockList, sShopID)
	}
		
/***********************************************************************
*
* getStock - Call our server script to determine the real time stock levels 
*	of the products in the given section
*	When the page is previewed from the desktop (within EC) we do not want to make
*	server calls for RTS levels. Therefore in this case we are passing in the 
*	list of stock monitored products and their offline stock level in sProdRefs and
*	sStockList parameters.
*
* Input:	sURL - the ajax script URL to call
*		sSID - the section ID list to be passed in to the ajax script or null if for a single product
*		sProdRefs - list of the products with stock monitoring on in this section or a single product refence
*		sStockList - the stock level of the products in the list above
*		sShopID - the shop ID (only used in host mode)
*
************************************************************************/

function getStock(sURL, sSID, sProdRefs, sStockList, sShopID)
	{
	var mapStockByRef = {};
	//
	// In case of preview use passed in data
	//
	 if  (sURL.indexOf("file://") == 0)
		{
		var arrProds = sProdRefs.split("|");
		var arrStock = sStockList.split("|");
		for (var i = 0; i < arrProds.length; i++)
			{
			var aRef = arrProds[i].split("!");
			var sKey = aRef[aRef.length - 1];
			mapStockByRef[sKey] = arrStock[i];
			}
		updateStockDisplay(mapStockByRef);
		}
	else
		{
		var ajaxRequest = new ajaxObject(sURL);
		ajaxRequest.callback = function (responseText) 
			{
			if (responseText.match(/^\d+$/))					// if response is a number
				{
				mapStockByRef[sProdRefs] = responseText;	// assume this is for a single product
				}
			else														// otherwise
				{
				mapStockByRef = responseText.parseJSON();	// parse response as JSON
				}
			updateStockDisplay(mapStockByRef);
			}
		//
		// If we don't supply a section ID, assume this is for a single product
		//
		var sParams = (sSID != null) ?
			("ACTION=GETSECTIONSTOCK&SID=" + sSID) :
			("ACTION=GETSTOCK&REF=" + sProdRefs);
		if (sShopID)
			{
			sParams += '&SHOP=' + sShopID;
			}
	   ajaxRequest.update(sParams, "GET");
		}
	}
	 
/***********************************************************************
*
* updateStockDisplay - dynamically update the DOM tree depending on stock levels
*
* Input:	mapStockByRef - product ref to stock level map
*
************************************************************************/

function updateStockDisplay(mapStockByRef)
	{ 
	//
	// For each product reference set the stock level and enable/disable 
	// the controlling DIV tags in the page source
	//
	var arrStockElems= getStockNodes();
	
	for (var nIndex = 0; nIndex < arrStockElems.length; nIndex++)
		{
		var aRef = arrStockElems[nIndex].id.split("_");
		var sProdRef = aRef[aRef.length - 1];
		var sIDStart = arrStockElems[nIndex].id.substring(0, arrStockElems[nIndex].id.length - sProdRef.length - 1); 
		if (mapStockByRef[sProdRef] != null) 
			{
			//
			// The stock level
			//
			if  (sIDStart == 'StockLevel')
				{
				arrStockElems[nIndex].innerHTML = mapStockByRef[sProdRef];
				}
			//
			// Out of stock
			//
			if  (sIDStart == 'EnableIfOutOfStock')
				{
				if (mapStockByRef[sProdRef] <= 0)
					{
					arrStockElems[nIndex].style.visibility = "visible";
					arrStockElems[nIndex].style.display = "inline";
					}
				else
					{
					arrStockElems[nIndex].style.visibility = "hidden";
					arrStockElems[nIndex].style.display = "none";
					}
				}

			if  (sIDStart == 'RemoveIfOutOfStock')
				{
				if (mapStockByRef[sProdRef] <= 0)
					{
					arrStockElems[nIndex].innerHTML = "";
					}
				}
			//
			// In stock
			//
			if  (sIDStart == 'EnableIfInStock')
				{
				if (mapStockByRef[sProdRef] > 0)
					{
					arrStockElems[nIndex].style.visibility = "visible";
					arrStockElems[nIndex].style.display = "inline";
					}
				else
					{
					arrStockElems[nIndex].style.visibility = "hidden";
					arrStockElems[nIndex].style.display = "none";
					}
				}
			if  (sIDStart == 'RemoveIfInStock')
				{
				if (mapStockByRef[sProdRef] > 0)
					{
					arrStockElems[nIndex].innerHTML = "";
					}
				}
			//
			// Generic flag to indicate ajax call went fine
			//
			if  (sIDStart == 'EnableIfStockOk')
				{
				arrStockElems[nIndex].style.visibility = "visible";
				arrStockElems[nIndex].style.display = "inline";
				}
			}
		}
	}
	
/***********************************************************************
*
* AttachEvent - Cross browser attachEvent function
*
* Input:	obj 			- object which event is to be attached
*		eventName 	- name of the event to listen
*		eventHandler	- the function to attach to the event
*
************************************************************************/

function AttachEvent(obj, eventName, eventHandler) 
	{
	if(obj) 
		{
		if (eventName.substring(0, 2) == "on") 
			{
			eventName = eventName.substring(2, eventName.length);
			}
		if (obj.addEventListener)
			{
			obj.addEventListener(eventName, eventHandler, false);
			} 
		else if (obj.attachEvent)
			{
			obj.attachEvent("on" + eventName, eventHandler);
			}
		}
	}

/***********************************************************************
*
* ValidateCartNameDetails - Validate the cart name and password for saving
*
* Returns:	true if data is OK
*
************************************************************************/

function ValidateCartNameDetails()
	{
	var elemDiv = document.getElementById("idRowCartNamePassword");
	if (!elemDiv)
		{
		return true;
		}
	if (elemDiv.style.display == "none")
		{
		elemDiv.style.display = "";
		return (false);
		}
	var elemInput = document.getElementById("idCartName");
	if (elemInput.value == '')
		{
		alert('Username must be filled in');
		return false;
		}
	elemInput = document.getElementById("idCartPassword");
	if (elemInput.value == '')
		{
		alert('Password must be filled in');
		return false;
		}
	return true;
	}

/***********************************************************************
*
* DeliveryCountryChanged - Handler for dynamic delivery state selection
*
************************************************************************/

function DeliveryCountryChanged()
	{
	CountryChanged('Delivery');
	}
	
/***********************************************************************
*
* InvoiceCountryChanged - Handler for dynamic invoice state selection
*
************************************************************************/

function InvoiceCountryChanged()
	{
	CountryChanged('Invoice');
	}
	
/***********************************************************************
*
* CountryChanged - Handler for dynamic state selection
*
* Input:	sLocationType	- 'Invoice' or 'Delivery'
*
************************************************************************/

function CountryChanged(sLocationType)
	{
	//
	// Get appropriate country select element
	//
	var cmbCountry = document.getElementById('lst' + sLocationType + 'Country');
	if (!cmbCountry)
		{
		return;
		}
	SetCountryTextFieldDisplay(sLocationType, '');
	//
	// Get appropriate state/region select element
	//

	var cmbState = document.getElementById('lst' + sLocationType + 'Region');
	if (!cmbState || !cmbState.options)
		{
		return;
		}
	//
	// Get appropriate state/region text element
	//
	var editState = document.getElementById('id' + sLocationType + 'RegionEdit');
	var sStateName = editState ? editState.value : '';
	//
	// Save current state value
	//
	var sCurrentState = cmbState.value;
	cmbState.options.length = 1;						// clear the state select options
	if (cmbCountry.value == "UndefinedRegion")	// if no country is selected
		{
		cmbState.style.display = "none";				// hide state select
		if (editState)
			{
			editState.style.display = "";
			}
		return;
		}
	var chkSeparateShip = document.getElementById("idSEPARATESHIP");
	var bSeparateShip = chkSeparateShip && chkSeparateShip.checked;
	//
	// Get the js country state map
	//
	var mapCountries = (sLocationType == 'Delivery') ? 
		g_mapDeliveryCountryStateMap : 
		g_mapInvoiceCountryStateMap;
	//
	// Get states from the map
	//
	var arrOptions = mapCountries[cmbCountry.value];
	if (!arrOptions && 
		sLocationType == 'Invoice' &&
		!bSeparateShip &&
		g_mapDeliveryCountryStateMap[cmbCountry.value] )
		{
		arrOptions = g_mapDeliveryCountryStateMap[cmbCountry.value];
		}
	if (!arrOptions)										// if there are no states
		{
		cmbState.style.display = "none";				// hide state select
		if (editState)
			{
			editState.style.display = "";
			}
		return;
		}
	cmbState.style.display = "";						// show the state select
	if (editState)
		{
		editState.style.display = "none";
		}
	var bFound = false;
	for (var i = 0; i < arrOptions.length; i += 2)		// go through state data
		{
		var oOption = document.createElement("OPTION");	// create an option
		oOption.text = arrOptions[i + 1];					// set state name
		oOption.value = arrOptions[i];						// set state code
		if (oOption.value == sCurrentState ||				// is this our current value?
			oOption.text == sStateName)						// or it matches the text field
			{
			bFound = true;											// mark as selected
			sCurrentState = oOption.value;
			oOption.selected = true;
			}
		cmbState.options.add(oOption);						// add option to select element
		}
	if (bFound)
		{
		cmbState.value = sCurrentState;						// restore current selection
		}
	}

/***********************************************************************
*
* SetCountryTextFieldDisplay - Set display of country text field
*
* Input:	sLocationType	- 'Invoice' or 'Delivery'
*			sDisplay			- '' to display or 'none' to hide
*
************************************************************************/

function SetCountryTextFieldDisplay(sLocationType, sDisplay)
	{
	var sTextID = (sLocationType == 'Delivery') ?
		'idDELIVERCOUNTRYText' :
		'idINVOICECOUNTRYText';
	var elemCountryText = document.getElementById(sTextID);
	if (elemCountryText)
		{
		//
		// Get appropriate country select element
		//
		var cmbCountry = document.getElementById('lst' + sLocationType + 'Country');
		elemCountryText.style.display = (cmbCountry && cmbCountry.value == '---') ? sDisplay : 'none';
		}
	}
	
/***********************************************************************
*
* SetDeliveryAddressVisibility - Handler for showing or hiding delivery address fields
*
************************************************************************/

function SetDeliveryAddressVisibility()
	{
	if (document.getElementById("idInvoiceRule") || document.getElementById("idDeliveryRule"))
		{
		SetAccountAddressVisibility();
		return;
		}
	SetInvoiceCountries();
	var chkSeparateShip = document.getElementById("idSEPARATESHIP");
	var sDisplay = "none";
	if (chkSeparateShip.checked)
		{
		sDisplay = "";
		}
	var cellSeparateShip = document.getElementById("idSeparateShipCell");
	if (document.getElementById("idDeliverHeader"))
		{
		if (cellSeparateShip)
			{
			cellSeparateShip.colSpan = sDisplay ? 1 : 2;
			}
		}
	SetTableCellsDisplay("idBothAddressesTable", "DeliverField", sDisplay);
	var chkResidential = document.getElementById("idINVOICERESIDENTIAL");
	if (chkResidential)
		{
		chkResidential.style.display = (chkSeparateShip.checked) ? 'none' : '';
		}
	InvoiceCountryChanged();
	}

/***********************************************************************
*
* SetAccountAddressVisibility - Handler for showing or hiding delivery address fields
*
************************************************************************/

function SetAccountAddressVisibility()
	{
	var sDisplay = "";
	var bNewInvoiceAddress = IsElementChecked("idINVOICEADDRESSSELECT_0");
	var bNewDeliverAddress = IsElementChecked("idDELIVERADDRESSSELECT_0");
	//
	// Hide address fields is neither 'Or enter new address is enabled
	//
	if (!bNewInvoiceAddress && !bNewDeliverAddress)
		{
		sDisplay = "none";
		}
	//
	// Show or hide table rows as appropriate
	//	
	var tblTarget = document.getElementById("idBothAddressesTable");
	if (!tblTarget)
		{
		return;
		}
	for (var nRow = 0; nRow < tblTarget.rows.length; nRow++)
		{
		var elemRow = tblTarget.rows[nRow];
		if (elemRow.className != "ShowAlways")
			{
			elemRow.style.display = sDisplay;
			}
		}
	if (sDisplay == 'none')								// nothing more to do if we're hiding rows
		{
		return;
		}
	//
	// Handle invoice fields
	//
	sDisplay = bNewInvoiceAddress ? "" : "none";
	SetTableCellsChildDisplay("idBothAddressesTable", "InvoiceField", sDisplay);
	if (sDisplay != 'none')
		{
		InvoiceCountryChanged();
		}
	//
	// Handle delivery fields
	//
	sDisplay = "none";
	if (bNewDeliverAddress)
		{
		if (!bNewInvoiceAddress ||						// if we're just showing delivery fields
			IsElementChecked("idSEPARATESHIP"))		// or we showing a different delivery address from user entered invoice address
			{
			sDisplay = "";									// display delivery fields
			}
		}
	SetTableCellsChildDisplay("idBothAddressesTable", "DeliverField", sDisplay);
	if (sDisplay != 'none')
		{
		DeliveryCountryChanged();
		}
	//
	// Hide different delivery address unless user is entering both addresses
	//
	var rowSeparateShip = document.getElementById("idSeparateShipRow");
	if (rowSeparateShip)
		{
		rowSeparateShip.style.display = bNewInvoiceAddress && bNewDeliverAddress ? '' : 'none';
		}
	}

/***********************************************************************
*
* IsElementChecked - Returns whether a radio-button or checkbox is checked 
*
* Input:	sID	- id of element to check
*
* Returns:	true if element exists and ic checked
*
************************************************************************/

function IsElementChecked(sID)
	{
	var elemCheck = document.getElementById(sID);
	if (elemCheck && elemCheck.checked)
		{
		return true;
		}
	return false;
	}

/***********************************************************************
*
* SetTableCellsDisplay - Show or hide cells in a table based on cell class name
*
* Input:	sTableID			- id of table
*			sClassName		- class name of cells to show or hide
*			sDisplay			- value for display style, "" to show, "none" to display
*
************************************************************************/

function SetTableCellsDisplay(sTableID, sClassName, sDisplay)
	{
	var tblTarget = document.getElementById(sTableID);
	if (!tblTarget)
		{
		return;
		}

	for (var nRow in tblTarget.rows)
		{
		var elemRow = tblTarget.rows[nRow];
		for (var nCell in elemRow.cells)
			{
			var elemCell = elemRow.cells[nCell];
			if (elemCell.className && elemCell.className == sClassName)
				{
				elemCell.style.display = sDisplay;
				}
			}
		}
	}
	
/***********************************************************************
*
* SetTableCellsChildDisplay - Show or hide cell's children in a table based on cell class name
*
* Input:	sTableID			- id of table
*			sClassName		- class name of cells to show or hide
*			sDisplay			- value for display style, "" to show, "none" to display
*
************************************************************************/

function SetTableCellsChildDisplay(sTableID, sClassName, sDisplay)
	{
	var tblTarget = document.getElementById(sTableID);
	if (!tblTarget)
		{
		return;
		}

	for (var nRow = 0; nRow < tblTarget.rows.length; nRow++)
		{
		var elemRow = tblTarget.rows[nRow];
		if (elemRow.className != 'ShowAlways')
			{
			for (var nCell = 0; nCell < elemRow.cells.length; nCell++)
				{
				var elemCell = elemRow.cells[nCell];
				if (elemCell.className && elemCell.className == sClassName)
					{
					for (var i = 0; i < elemCell.childNodes.length; i++)
						{
						var elemChild = elemCell.childNodes[i];
						if (elemChild.style && elemChild.id.indexOf('pcaDiv') != 0)
							{
							elemCell.childNodes[i].style.display = sDisplay;
							}
						}
					}
				}
			}
		}
	}
	
/***********************************************************************
*
* SetShoppingCartVisibility - Handler for showing or hiding cart details
*
************************************************************************/

function SetShoppingCartVisibility()
	{
	var elemShowHide = document.getElementById("idShowHide");
	if (!elemShowHide)
		{
		return;
		}

	var spanShoppingCart = document.getElementById("idShoppingCartGrid");
	if (!spanShoppingCart)
		{
		return;
		}
	var elemCartHeadingTotal = document.getElementById("idCartHeadingTotal");
	var elemCartChangeCell = document.getElementById("idCartChangeCell");
	if (spanShoppingCart.style.display == "none")
		{
		spanShoppingCart.style.display = "";
		elemShowHide.innerHTML = 'hide';
		elemCartHeadingTotal.style.display = 'none';
		if (elemCartChangeCell)
			{
			document.getElementById("idCartChangeCell").style.display = '';
			}
		}
	else
		{
		spanShoppingCart.style.display = "none";
		elemShowHide.innerHTML = 'show';
		elemCartHeadingTotal.style.display = '';
		if (elemCartChangeCell)
			{
			document.getElementById("idCartChangeCell").style.display = 'none';
			}
		}
	}

/***********************************************************************
*
* SetCreditCardFieldsVisibility - Handler for showing or hiding credit card fields
*
************************************************************************/

function SetCreditCardFieldsVisibility()
	{
	var nPaymentMethod = GetPaymentMethod();

	var sDisplay = "none";
	if (nPaymentMethod == "10005")
		{
		sDisplay = "";
		}
	SetTableRowsDisplay("idPaymentMethodTable", "CreditCardField", sDisplay);
	}

/***********************************************************************
*
* SetTableRowsDisplay - Show or hide rows in a table based on row class name
*
* Input:	sTableID			- id of table
*			sClassName		- class name of rows to show or hide
*			sDisplay			- value for display style, "" to show, "none" to display
*
************************************************************************/

function SetTableRowsDisplay(sTableID, sClassName, sDisplay)
	{
	var tblTarget = document.getElementById(sTableID);
	if (!tblTarget)
		{
		return;
		}
	for (var nRow in tblTarget.rows)
		{
		var elemRow = tblTarget.rows[nRow];
		if (elemRow.className && elemRow.className == sClassName)
			{
			elemRow.style.display = sDisplay;
			}
		}
	}

/***********************************************************************
*
* CheckForm - Validate a form before submission
*
* Input:	elemBtn	- element doing the submission
*
* Returns:	true to let form submit, false to prevent bubbling up
*
************************************************************************/

function CheckForm(elemBtn)
	{
	//
	// Find the form element in ancestors
	//
	var elemForm = elemBtn.parentElement ? elemBtn.parentElement : elemBtn.parentNode;
	while (elemForm &&
		elemForm.tagName != "FORM")
		{
		elemForm = elemForm.parentElement ? elemForm.parentElement : elemForm.parentNode;
		}
	if (!elemForm)											// if form doesn't exist, bail out
		{
		return true;
		}
	//
	// Decide whether we should validate the confirmation email address
	// We don't confirm emails if we're selecting an account address
	// or a delivery address if it is the same as invoice address
	//
	var bAccountCustomer = (document.getElementsByName('INVOICEADDRESSSELECT').length > 0);
	var bSkipInvoice = false;
	if (bAccountCustomer)
		{
		bSkipInvoice = !IsElementChecked("idINVOICEADDRESSSELECT_0");	// skip invoice if we're selecting an address
		}
	var chkSeparateShip = document.getElementById('idSEPARATESHIP');
	var bSkipDeliver = false;
	if (bAccountCustomer)
		{
		bSkipDeliver = !IsElementChecked("idDELIVERADDRESSSELECT_0");	// skip delivery if we're selecting an address
		}
	if (!bSkipDeliver)																// if we're not selecting an address
		{
		bSkipDeliver = (chkSeparateShip && !chkSeparateShip.checked);	//	skip if delivery is same as invoice
		}
	if (bSkipInvoice && bSkipDeliver)											// if we skip both addresses
		{
		return true;																	// nothing to check
		}

	var arrDescendants = GetAllElements(elemForm);
	for (var i = 0; i < arrDescendants.length; i++)
		{
		var elemThis = arrDescendants[i];
		if ((elemThis.id == 'idINVOICEEMAIL_CONFIRM' && !bSkipInvoice) ||
			(elemThis.id == 'idDELIVEREMAIL_CONFIRM' && !bSkipDeliver))
			{
			var elemEmail = document.getElementById(elemThis.id.replace(/_CONFIRM$/, ''));
			if (elemEmail.style.display != 'none' && elemEmail.value != elemThis.value)
				{
				var sMsg = GetLabelText(elemThis) + "\n\n";
				sMsg += "'" + elemThis.value + "' does not match '" + elemEmail.value + "'";
				alert(sMsg);
				elemThis.focus();
				return false;
				}
			}
		if ((elemThis.id == 'idNEWCUSTOMERPASSWORD2') &&
			(IsElementChecked('idCREATEANACCOUNT') ||
			document.getElementById('idCREATEANACCOUNT') == null))
			{	
			var elemPwd = document.getElementById('idNEWCUSTOMERPASSWORD');
			if (elemPwd.style.display != 'none' && elemPwd.value != elemThis.value)
				{
				var sMsg = PASSWORD_MATCH_ERROR;
				alert(sMsg);
				elemThis.focus();
				return false;
				}
			}
		}
	if (bSkipInvoice && !bSkipDeliver)
		{
		chkSeparateShip.checked = true;
		}
	return true;
	}	

/***********************************************************************
*
* GetAllElements - Get all descendants of an element
*
* Input:	elemParent	- parent element
*
* Returns:	collection of descendant elements
*
************************************************************************/

function GetAllElements(elemParent)
	{
	if (elemParent.all)										// IE-specific
		{
		return elemParent.all;
		}
	else if (elemParent.getElementsByTagName)			// W3C compliant browsers
		{
		return elemParent.getElementsByTagName('*');
		}
	}
	
/***********************************************************************
*
* SubmitPSPForm - Submit a form to a PSP
*
* Returns:	true to let form submit, false to prevent bubbling up
*
************************************************************************/
var g_sConfirmOrderInitText = '';

function SubmitPSPForm()
	{
	var sSendingOrder = "Saving your order";
	var elemConfirmOrder = document.getElementById("idBtnConfirm");
	if (elemConfirmOrder.value == sSendingOrder)
		{
		if (confirm("Are you sure") == false)
			{
			return false;
			}
		}
	else
		{
		g_sConfirmOrderInitText = elemConfirmOrder.value;
		}
	elemConfirmOrder.value = sSendingOrder;
	var nPaymentMethod = GetPaymentMethod();
	if (nPaymentMethod == -1)
		{
		return true;
		}
	if (nPaymentMethod >= 10000 && 
		nPaymentMethod < 30000)							// if this ia an inbuilt payment method
		{
		return true;										// don't submit PSP form
		}
	
	GetPSPFormAndSubmit(nPaymentMethod);
	return false;
	}	

/***********************************************************************
*
* GetPaymentMethod - Get the payment method
*
* Returns:	payment method or -1 if not found
*
************************************************************************/

function GetPaymentMethod()
	{
	var cmbPaymentMethod = document.getElementById("idPAYMENTMETHOD");
	if (cmbPaymentMethod)								// if we have an element with correct id
		{
		return cmbPaymentMethod.value;				// return it
		}
	//
	// Get radio buttons or hidden by name if present
	//
	var collPaymentMethods = document.getElementsByName("PAYMENTMETHOD");
	if (!collPaymentMethods)
		{
		return -1;
		}
	if (collPaymentMethods.length == 1)				// might have a single method in which case it will be hidden input
		{
		return collPaymentMethods[0].value;
		}
	for (var i = 0; i < collPaymentMethods.length; i++)	// find checked radio button
		{
		if (collPaymentMethods[i].checked)
			{
			return collPaymentMethods[i].value;
			}
		}
	return -1;
	}

/***********************************************************************
*
* GetPSPFormAndSubmit - Submit a form to a PSP
*
* Input:	nPaymentMethod	- payment method
*
************************************************************************/

function GetPSPFormAndSubmit(nPaymentMethod)
	{
	var ajaxRequest = new ajaxObject(document.location.href.split('?')[0]);
	ajaxRequest.callback = function (responseText) 
		{
		if (responseText.substring(0, 6) == "Error:")
			{
			alert(responseText);
			var elemConfirmOrder = document.getElementById("idBtnConfirm");
			if (elemConfirmOrder)
				{
				elemConfirmOrder.value = g_sConfirmOrderInitText;
				}
			return;
			}
		//
		// Get the placeholder span for the PSP form
		//
		var elemSpanPSPForm = document.getElementById("idSpanPSPForm");
		if (!elemSpanPSPForm)
			{
			return;
			}
		elemSpanPSPForm.innerHTML = responseText;
		//
		// Get the PSP form
		//
		var elemPSPForm = document.getElementById("idPSPForm");
		if (!elemPSPForm)
			{
			return;
			}
		//
		// Submit the PSP form
		//
		elemPSPForm.submit();
		}
	var sParams = "ACTION=GETPSPFORM&PAYMENTMETHOD=" + nPaymentMethod;
	var elemPONumber = document.getElementsByName('PAYMENTPONO');
	if (elemPONumber.length)
		{
		sParams += '&PAYMENTPONO=' + escape(elemPONumber[0].value);
		}
	var elemPayUserDef = document.getElementsByName('PAYMENTUSERDEFINED');
	if (elemPayUserDef.length)
		{
		sParams += '&PAYMENTUSERDEFINED=' + escape(elemPayUserDef[0].value);
		}
   ajaxRequest.update(sParams, "GET");
	}

/***********************************************************************
*
* SFDropDownMenu - Javascript function to handle Suckerfish drop-down menus in IE
*
* Input:	sID	- ID of the <UL> element
*
************************************************************************/

function SFDropDownMenu(sID) 
	{
	var collElems = document.getElementById(sID).getElementsByTagName("LI");
	for (var i = 0; i < collElems.length; i++) 
		{
		collElems[i].onmouseover = function() 
			{
			this.className += " sfhover";
			}
		collElems[i].onmouseout = function() 
			{
			this.className = this.className.replace(new RegExp(" sfhover\\b"), "");
			}
		}
	}
	
/***********************************************************************
*
* ShowHideHelp - Show or hide the help for a field under the field
*
* Input:	elemSource	- the field control
*			sDisplay		- string to set style.display ('' to show, 'none' to hide)
*
************************************************************************/

function ShowHideHelp(elemSource, sDisplay)
	{
	var elemHelp = document.getElementById(elemSource.id + 'help');	// get associated help element
	if (!elemHelp)
		{
		return;
		}
	elemHelp.style.display = sDisplay;											// show or hide help element
	}

/***********************************************************************
*
* ShowHideHelpDiv - Show or hide the help for a field in the help area
*
* Input:	elemSource	- the field control
*			sDisplay		- string to set style.display ('' to show, 'none' to hide)
*
************************************************************************/

function ShowHideHelpDiv(elemSource, sDisplay)
	{
	var elemHelp = document.getElementById(elemSource.id + 'help');	// get associated help element
	if (!elemHelp)
		{
		return;
		}
	var elemHelpElem = document.getElementById('idCheckoutHelp');		// get help display element
	if (!elemHelpElem)
		{
		return;
		}
	var sText = elemHelp.innerHTML;
	var elemLabel = document.getElementById(elemSource.id + 'label');	// try and get label area
	if (elemLabel &&
		elemLabel.className == 'actrequired')									// if it's a required field
		{
		sText += ' This is a required field.';									// tell user
		}
	elemHelpElem.innerHTML = sDisplay == '' ? sText : '';					// set html for help display
	}

/***********************************************************************
*
* GetLabelText - Get the label text associated with a control
*
* Input:	elemSource	- user UI element
*
************************************************************************/

function GetLabelText(elemSource)
	{
	var elemLabel = document.getElementById(elemSource.id + 'label');	// try and get label area
	if (!elemLabel)
		{
		elemLabel = document.getElementById(elemSource.id.replace(/DELIVER/, 'INVOICE') + 'label');
		}
	if (elemLabel)
		{
		var sLabel = elemLabel.innerHTML;
		sLabel = sLabel.replace(/(\n|\t)/, ' ');
		sLabel = sLabel.replace(/<.*?>/g, '');
		sLabel = sLabel.replace(/\s*\*$/, '');
		return sLabel;
		}
	return '';
	}

/***********************************************************************
*
* SetFocusToID - Set focus to element with supplied id
*
* Input:	sID	- id of element
*
************************************************************************/

function SetFocusToID(sID)
	{
	var elemFocus = document.getElementById(sID);							// get element to set focus to
	if (!elemFocus)
		{
		return;
		}
	if (elemFocus.style.display != 'none')
	elemFocus.focus();																// set focus
	}
	
/***********************************************************************
*
* SetInvoiceCountries - Populate the invoice countries dropdown depending upon
*		different address checkbox
*
************************************************************************/
var g_sInvoiceCountryCode = '';

function SetInvoiceCountries()
	{
	var cmbCountry = document.getElementById('lstInvoiceCountry');
	if (!cmbCountry || !cmbCountry.options)
		{
		return;
		}
	var editCountry  = document.getElementById('idINVOICECOUNTRYText');
	var chkSeparateShip = document.getElementById('idSEPARATESHIP');
	var bSeparateShip = (chkSeparateShip && chkSeparateShip.checked) ? true : false;
	//
	// Save current country value
	//
	var sCurrentCountryCode = cmbCountry.value ? cmbCountry.value : g_sInvoiceCountryCode;
	var sCurrentCountryText = ((sCurrentCountryCode == '' || sCurrentCountryCode == '---') && editCountry) ? editCountry.value : '';
	cmbCountry.options.length = 1;						// clear the state select options except for 'Select country'
	var sFoundCode = '';
	var sFoundNameCode = '';
	for (var i in g_arrCountries)
		{
		var arrCountry = g_arrCountries[i];
		var bAdd = true;
		if (g_bInvoiceLocationRestrictive)
			{
			if (!bSeparateShip && g_bDeliveryLocationRestrictive)
				{
				bAdd = arrCountry[2] && arrCountry[3];
				}
			else
				{
				bAdd = arrCountry[2];
				}
			}
		else if (g_bDeliveryLocationRestrictive && !bSeparateShip)
			{
			bAdd = arrCountry[3];
			}
		else
			{
			bAdd = arrCountry[2] || arrCountry[3];
			}
		if (bAdd)
			{
			var oOption = document.createElement("OPTION");	// create an option
			oOption.value = arrCountry[0];						// set country code
			oOption.text = arrCountry[1];							// set country name
			if (sCurrentCountryCode && oOption.value == sCurrentCountryCode)				// if it matches the code
				{
				sFoundCode = oOption.value;
				}
			if (sCurrentCountryCode != '---' && oOption.text == sCurrentCountryText)				// if it matches the code
				{
				sFoundNameCode = oOption.value;
				}
			cmbCountry.options.add(oOption);						// add option to select element
			}
		}
	if (sFoundCode)
		{
		cmbCountry.value = sFoundCode;
		}
	if (sFoundNameCode)
		{
		cmbCountry.value = sFoundNameCode;
		}
	if (cmbCountry.value)
		{
		g_sInvoiceCountryCode = cmbCountry.value;
		}
	}

/***********************************************************************
*
* StateDropdownChanged - The selection in state dropdown has changed
*
* Input:	cmbState	- state dropdown
*
************************************************************************/

function StateDropdownChanged(cmbState)
	{
	//
	// Get edit control
	//
	var idEdit = (cmbState.id.indexOf('Invoice') != -1) ? 'idInvoiceRegionEdit' : 'idDeliveryRegionEdit';
	var editState  = document.getElementById(idEdit);
	if (!editState ||									// if there's no text control
		cmbState.value == 'UndefinedRegion')	// or the state is undefined
		{
		return;											// quit
		}
	//
	// Update the text control with the text from combo
	//
	var nIndex = cmbState.selectedIndex;
	editState.value = cmbState.options[nIndex].text;
	}
	
/***********************************************************************
*
* LoadXMLDoc - Load the doc specified by input URL and return the XML response
*
* Input:	sURL			- URL of document
*			bReturnDoc	- true if we want DOM document, false if we want XML string
*
* Returns:	DOM document or XML string
*
************************************************************************/

function LoadXMLDoc(sURL, bReturnDoc)
	{
	if (window.XMLHttpRequest)
		{
		xhttp=new XMLHttpRequest();
		}
	else
		{
		xhttp=new ActiveXObject("Microsoft.XMLHTTP");
		}
	xhttp.open("GET", sURL, false);
	xhttp.send(null);
	if (bReturnDoc)
		{
		return xhttp.responseXML;
		}
	else
		{
		return xhttp.responseText;
		}
	}

/***********************************************************************
*
* DOMDocFromXML - Create a DOM document from an XML string
*
* Input:	sXML	- source XML string
*
* Returns:	DOM document or null if no parser supported
*
************************************************************************/

function DOMDocFromXML(sXML)
	{
	var docDOM = null;
	if (window.ActiveXObject)							// IE code
		{
		docDOM = new ActiveXObject("Microsoft.XMLDOM");
		docDOM.async = "false";
		docDOM.loadXML(sXML);
		}
	else if (window.DOMParser)							// other browsers
		{
		var oParser = new DOMParser();
		docDOM = oParser.parseFromString(sXML, "text/xml"); 
		}
	return docDOM;
	}

/***********************************************************************
*
* DisplayFeefoFeedback - Display the feefo XML feed for products or the whole site
*
* Input:	nLimit	- the max number of comments to be displayed
*			sSiteURL	- URL of the acatalog folder (needed to prefix extra data)
*			sCGIURL	- URL to the cart script wrapper
*			sLogon	- feefo logon
*			sProduct - the product reference (if this is an empty string, site feed displayed)
*			sShopID	- shop ID for host mode (empty string in non-host mode)
*
************************************************************************/

function DisplayFeefoFeedback(nLimit, sSiteURL, sCGIURL, sLogon, sProduct, sShopID)
	{
	var sParams = escape("?logon=" + sLogon);			// escape the parameter
	//
	// If product ref specified then add it to the param String
	//
	var sNode = "FeefoFeedback";
	if (sProduct != "")
		{
		sParams += escape("&vendorref=" + sProduct);
		sNode += "_" + sProduct;
		}
	//
	// Add the limit parameter
	//
	sParams += escape("&limit=" + nLimit);
	//
	// We need cdata
	//
	sParams += escape("&mozillahack=true");
	//
	// Load the files
	//
	var sFeefoURL = sCGIURL + "?ACTION=FEEFOXML&FEEFOPARAM=" + sParams;
	if (sShopID)											// add shop id in host mode
		{
		sFeefoURL += "&SHOP=" + escape(sShopID);
		}
	var xml = LoadXMLDoc(sFeefoURL, true); //?logon=www.examplesupplier.com");
	if (xml == null || xml.xml == "")
		{
		return;
		}
	var sXslXML = LoadXMLDoc(sSiteURL + "feedback.xsl", false);	// get xsl as string 
	//
	// Convert css and image files to full URLs
	//
	var reFiles = /(feefo\.css|plus\.gif|minus\.gif)/ig;
	sXslXML = sXslXML.replace(reFiles, sSiteURL + "$1");			// convert to full URLs
	var docXSL = DOMDocFromXML(sXslXML);								// create a DOM doc from XML string
	//
	// code for IE
	//
	if (window.ActiveXObject)
		{
		ex = xml.transformNode(docXSL);
		document.getElementById(sNode).innerHTML = ex;
		}
	//
	// code for Mozilla, Firefox, Opera, etc.
	//
	else if (document.implementation && document.implementation.createDocument)
		{
		xsltProcessor = new XSLTProcessor();
		xsltProcessor.importStylesheet(docXSL);
		resultDocument = xsltProcessor.transformToFragment(xml,document);
		document.getElementById(sNode).appendChild(resultDocument);
		}
	}

/***********************************************************************
*
* ShowBackLink - Display the back link for SPP pages
*
************************************************************************/

function ShowBackLink()
	{
	var sLastSection = getCookie('LAST_SECTION_URL');	// get last section page URL
	if (!sLastSection)
		{
		return;
		}
	var elemBackLink = 
		document.getElementById('idSPPBackLink');			// get the back link
	if (!elemBackLink)
		{
		return;
		}
	elemBackLink.href = sLastSection;						// set the url						
	elemBackLink.style.display = '';							// show the link
	}
	
/***********************************************************************
*
* CheckPassword - Do the passwords match
*
* Input:	elemPwd		- password element
*			elemRetype	- confirm password element
*
* Returns:	true if the two passwords match
*
************************************************************************/

function CheckPassword(elemPwd, elemRetype)
	{	
	if (!elemPwd.value ||
		!elemRetype.value ||
		elemPwd.value != elemRetype.value)
		{
		var sMsg = PASSWORD_MATCH_ERROR;
		var elemFocus = elemPwd;
		if (!elemPwd.value)
			{
			sMsg = 'Please enter a value for ' + GetLabelText(elemPwd);
			}
		else if (!elemRetype.value)
			{
			sMsg = 'Please enter a value for ' + GetLabelText(elemRetype);
			elemFocus = elemRetype;
			}
		alert(sMsg);
		elemFocus.focus();
		return false;
		}
	return true;	
	}

/***********************************************************************
*
* GetScriptURL - Get the current location with no parameters
*
* Returns:	current location with any parameters removed
*
************************************************************************/

function GetScriptURL()
	{
	var sURL = document.location.href;
	return sURL.split('?')[0];
	}

/***************************************************************
*
* IsLoggedIn	- Returns whether the user is logged in
*
***************************************************************/

function IsLoggedIn()
	{
	var sBusinessCookie = getCookie('ACTINIC_BUSINESS');
	if (!sBusinessCookie)
		{
		return false;
		}
	var arrFields = sBusinessCookie.split(/\n/);
	for (var i = 0; i < arrFields.length; i++)
		{
		var arrNameValue = arrFields[i].split(/\t/);
		if (arrNameValue[0] == 'USERNAME' &&
			arrNameValue[1] != '')
			{
			return true;
			}
		}
	return false;
	}

/***************************************************************
*
* GetScriptPrefix	- Returns the 2 letter script prefix
*
***************************************************************/

function GetScriptPrefix()
	{
	var nLastSlash = location.pathname.lastIndexOf('/');
	if (nLastSlash != -1)
		{
		var sScript = location.pathname.substr(nLastSlash + 1);
		return sScript.substr(0, 2);
		}
	}

/***************************************************************
*
* SetBusinessCookies	- Sets business cookies for customer accounts in split SSL
*
* Input:	sBusinessCookie	- business cookie or undefined if logging out
*			sCartCookie			- cart cookie (ignored if logging out)
*
***************************************************************/

function SetBusinessCookies(sBusinessCookie, sCartCookie)
	{
	if (!sBusinessCookie)
		{
		setCookie('CART_CONTENT', 'CART_TOTAL\t0\tCART_COUNT\t0');
		setCookie('ACTINIC_BUSINESS', 'BASEFILE');
		document.location.replace(document.location.href.replace(/#logout$/, ''));
		}
	}

/***********************************************************************
*
* Actinic Mega Menu
*
* Variables:
*	timeout 	- time in ms for hover event to show/hide menu
*	closeTimer 	- delay time in ms for menu to close when mouseout event fired
*	menuParent 	- object for holding menus parent element
*	menuitem 	- object for holding menu element
*	 
* Author:				Fergus Weir
*
************************************************************************/	
var timeout	= 500;
var closeTimer = 0;
var menuParent = 0;
var menuItem = 0;

/***********************************************************************
*
* $tb		-	Shortcut for getElementById(element)
* Returns:	-	element with matching ID
*
* Author:				Fergus Weir
*
************************************************************************/
var $ge = function(id) {
  return document.getElementById(id);
};

/***********************************************************************
*
* mmClose		-	Hides the menu element
* Returns:		-	nothing
*
* Author:				Fergus Weir
*
************************************************************************/
function mmClose() {
  if (menuItem) menuItem.style.display = 'none';
  if (menuParent) {
    menuParent.className = '';
  }
}
/***********************************************************************
*
* mmCloseTime		-	Resets mega menu closing timer
* Returns:			-	nothing
*
* Author:				Fergus Weir
*
************************************************************************/
function mmCloseTime() {
  closeTimer = window.setTimeout(mmClose, timeout);
}
/***********************************************************************
*
* mmCancelCloseTime	-	cancels the resetting of mega menu closing timer
* Returns:	 		-	nothing
*
* Author:				Fergus Weir
*
************************************************************************/
function mmCancelCloseTime() {
  if (closeTimer) {
    window.clearTimeout(closeTimer);
	closeTimer = null;
  }
  if (menuParent) {
    menuParent.className = 'sel';
  }
}
/***********************************************************************
*
* mmOpen		-	Function is called from mouseOver event and positions
*                   the mega menu drop down in correct position as well
*                   as ensuring it is made visible
* Returns:		-	nothing
*
* Author:				Fergus Weir
*
************************************************************************/
// open hidden layer
function mmOpen(id) {	
  // cancel close timer
  mmCancelCloseTime();
  // close old layer
  mmClose();

  // get new layer and show it
  menuDiv = $ge('mega-menu');
  menuParent = $ge('main-link' + id);
  menuItem = $ge('tc' + id);
  //show the menu to enable dimension properties and show on page
  menuItem.style.display = 'block';
  //reposition 
  //get position and size dimensions
  var topNavWidth = menuDiv.offsetWidth;
  var menuDropWidth = menuItem.offsetWidth;
  var menuPosOnPage = findLeftPos(menuDiv);
  var itemPosOnPage = findLeftPos(menuParent);
 // the width from the default menu start position to the edge of the container
  var MenuPlaceholderwidth = (topNavWidth - itemPosOnPage);
  //alert('menu placeholder width = ' + MenuPlaceholderwidth);
  
  
  //if the menu to display is greater than the top nav 
  if (topNavWidth < menuDropWidth) {
	//get difference
	var widthDifference = menuDropWidth - topNavWidth;
	//center item
	menuItem.style.left = (-1 * (itemPosOnPage +  Math.floor((widthDifference/2)) - menuPosOnPage)) + "px";
  }
  else if (topNavWidth < ((itemPosOnPage-menuPosOnPage) + menuDropWidth))  {
   // off the page so align to right
   menuItem.style.left = -1 * (((itemPosOnPage-menuPosOnPage) + menuDropWidth) - topNavWidth) + "px";
	}
  else {
	//not wider than menu; not off the page, so set to standard
	menuItem.style.left = 0 + "px";
   }
}

/***********************************************************************
*
* findPos		-	Finds the  left position of an element in the window
* Returns:		-   x coordinate of object in visible window
*
* Author:				Fergus Weir
*
************************************************************************/
function findLeftPos(obj) {
	var curleft = 0;
	if (obj.offsetParent) {
	do {
		curleft += obj.offsetLeft;
		} while (obj = obj.offsetParent);
	return curleft;
}
}
	
