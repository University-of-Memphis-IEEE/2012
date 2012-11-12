
function createBriefcase(productId) {
  if (productId != "") {
    var prefix2 = productId.substring(0,2);
    if (prefix2 == "AD") {  prefix2 = "DC"; }
    document.write('<span id=slidingProductBASEPART:::'+productId+' class=sliding_product><a onclick=addToBasket("BASEPART:::'+productId+'"); name=#><img src=http://www.national.com/analogs/images/briefcase.gif style="position: relative; top:3px;" alt="Add '+productId+' into My Briefcase"> <a href=/pf/'+prefix2+'/'+productId+'.html>'+productId+'</a></a></span>');
  }
}

