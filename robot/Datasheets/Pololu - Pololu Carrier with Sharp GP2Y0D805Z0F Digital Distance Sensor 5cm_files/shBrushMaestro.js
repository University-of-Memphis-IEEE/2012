/* Maestro script syntax contributed by Paul Grayson 
 *
 * Updated to version 3 of SyntaxHighlighter by Ryan Mulligan
 */
;(function()
{
  // CommonJS
  typeof(require) != 'undefined' ? SyntaxHighlighter = require('shCore').SyntaxHighlighter : null;

  function Brush()
  {
    var keywords = 'GOTO SUB BEGIN WHILE REPEAT IF ENDIF ELSE';

    var builtins = 'QUIT LITERAL LITERAL8 LITERAL_N LITERAL8_N RETURN JUMP JUMP_Z DELAY GET_MS DEPTH DROP DUP OVER PICK SWAP ROT ROLL BITWISE_NOT BITWISE_AND BITWISE_OR BITWISE_XOR SHIFT_RIGHT SHIFT_LEFT LOGICAL_NOT LOGICAL_AND LOGICAL_OR NEGATE PLUS MINUS TIMES DIVIDE MOD POSITIVE NEGATIVE NONZERO EQUALS NOT_EQUALS MIN MAX LESS_THAN GREATER_THAN SERVO SERVO_8BIT SPEED ACCELERATION GET_POSITION GET_MOVING_STATE LED_ON LED_OFF'

    this.regexList = [
      { regex: SyntaxHighlighter.regexLib.singleLinePerlComments, css: 'comments' }, // one line comments
      { regex: new RegExp('\\S+:', 'g'),                          css: 'label' },   // labels
      { regex: new RegExp(this.getKeywords(keywords), 'gmi'),     css: 'keyword' }, // keywords
      { regex: new RegExp(this.getKeywords(builtins), 'gmi'),     css: 'builtin' }  // builtins
    ];

    //this.CssClass = 'dp-rb';
    //this.Style = '.dp-rb .symbol { color: #a70; }' + '.dp-rb .variable { color: #a70; font-weight: bold; }';
  };


  Brush.prototype = new SyntaxHighlighter.Highlighter();
  Brush.aliases   = ['maestro'];

  SyntaxHighlighter.brushes.Maestro = Brush;

  // CommonJS
  typeof(exports) != 'undefined' ? exports.Brush = Brush : null;
})();