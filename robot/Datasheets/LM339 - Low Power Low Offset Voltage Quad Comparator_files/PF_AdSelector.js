function selectVideo(count) {
  for (var x = 0; x <= 30; x++) {
    var vCell = document.getElementById("videoSeq" + x);
    if (vCell != null) {
      vCell.className = 'viewPFDIVhide';
    }
  }
  document.getElementById("videoSeq" + count).className = 'viewPFDIVshow';
}

function showPFElement(count) {
  for (var x = 0; x <= 12; x++) {
    var cCell = document.getElementById("AdSelectorContent-" + x);
    if (cCell != null) {
      cCell.className = 'viewPFDIVhide';
    }
    var sCell = document.getElementById("AdSelectorCell-" + x);
    if (sCell != null) {
      sCell.className = 'navselector-viewpf-regular';
    }
  }
  document.getElementById("AdSelectorContent-" + count).className = 'viewPFDIVshow';
  document.getElementById("AdSelectorCell-" + count).className = 'navselector-viewpf-selected';
  if (count == 1) {
    defaultTable();
    setTimeout(updateSeries,2800);
    runSlowMo();
  }
  return true;
}

function updURL(updText) {
  var myUpdURL=new Array();
  myUpdURL[0]="#Overview";
  myUpdURL[1]="#Compare";
  myUpdURL[2]="#Diagrams";
  myUpdURL[3]="#Parametrics";
  myUpdURL[4]="#Documents";
  myUpdURL[5]="#Order";
  myUpdURL[6]="#Packaging";
  myUpdURL[7]="#Tools";
  myUpdURL[8]="#Reliability";
  myUpdURL[9]="#ObsoleteVersions";
  myUpdURL[10]="#Videos";
  myUpdURL[11]="#Boards";
  myUpdURL[12]="#Custom";
  var myLocHREF = document.location.href;
  myLocHREF = myLocHREF.replace(/http:\/\/www.national.com/gi, "");
  myLocHREF = myLocHREF.replace(/http:\/\/stage.national.com:8888/gi, "");
  var xURL = -1;
  for (var x = 0; x <= 12; x++) {
    if (myLocHREF.match(myUpdURL[x])) {
      xURL = x;
    }
  }
  if (updText < 0) {
    if (xURL < 0) {
      updText = 0;
    } else {
      updText = xURL;
    }
  } else if (updText > 12) {
    updText = 0;
  }
  window.location.href = myUpdURL[updText];
  showPFElement(updText);
  
  //pageTracker._trackPageview(myLocHREF + myUpdURL[updText]);
}
         
function showPFElementOLD(count)
{
        var e = document.getElementById("AdSelectorContent-");
        //alert(e.innerHTML);
        var src = document.getElementById("AdSelectorContent-" + count).innerHTML;
        src = src.replace(/^\s+|\s+$/g, '') ;
        //alert("src='" + src + "'");
        if(src == null || src == '' || src == 'null')
        {
                var src = "<a href='" + href + "'>" + "</a>";
        }
        e.innerHTML = src;
        e.style.display="block";
        e.className="viewPFDIV";


        for (var x = 1; x <= 28; x++)
        {
                var tcell = document.getElementById("AdSelectorCell-" + x);
                if(tcell != null)
                        tcell.className = "navselector-viewpf-regular";
        }

        var cell = document.getElementById("AdSelectorCell-" + count);
        cell.className = "navselector-viewpf-selected";
        return true;
}
                                                                       
function selectPFElement(count)
{
        //alert("AdSelectorCell-" + count);
        var cell = document.getElementById("AdSelectorCell-" + count);
        cell.className = "navselector-viewpf-selected";         
        var e = document.getElementById("AdSelectorContent-");
        e.className="viewPFDIV";
}

