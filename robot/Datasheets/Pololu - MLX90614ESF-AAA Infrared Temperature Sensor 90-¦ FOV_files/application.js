// Place your application-specific JavaScript functions and classes here
// This file is automatically included by javascript_include_tag :defaults

function highlightYellow(element) {
  if (element == null)
    return;
  element.style['background-color'] = '#FFFF99';
  (function(){
    function updateBackgroundColor(i) {
      blue = parseInt(153+i*102/255).toString(16);

      element.style.backgroundColor = '#FFFF'+blue;

      if (i >= 221)
      {
	element.style.backgroundColor = "#FFFFEE";
	return;
      }
      else
	setTimeout(function() {updateBackgroundColor(i+1);},1);
    };
    updateBackgroundColor(0, element);
  })();
}