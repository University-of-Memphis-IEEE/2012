
function showTEAMnsid(productId) {
  if (productId != "" && chicken == "SOUP") {
    //document.write("<a href='http://www.national.com/jit/dl.cgi/NationalSemi_DistributionTeam.xls' target='_parent'><img src='http://www.national.com/analogs/images/national3/distribution_team_pf_btn.gif' border=0></a>");
  }
}

function showNewTEAMnsid(productId) {
  if (productId != "" && satay == "HOUSE") {
    //document.write(basepnNewTEAM + NewTEAMa + basepnNewTEAM1 + NewTEAMb + basepnNewTEAM2;);
  }
}

function showEVM(divId,productId,productQty) {
  if (divId != "" && satay == "HOUSE") {
    document.getElementById(divId).innerHTML = "<table class=datatable><tr><td><a href='http://www.national.com/order/evm.cgi?nsid="+productId+"'>Order Sample</a></td><td>"+productQty+"</td></tr></table>";
  }
}
