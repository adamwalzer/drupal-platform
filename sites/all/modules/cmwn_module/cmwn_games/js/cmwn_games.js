(function ( $ ) {

    var cmwn_games_url = location.protocol + "//" + location.host + "/";
    
    //GET WEBFORM (action item step) object from drupal platform.
    $.fn.cmwn_games_object = function(options, callback) {
      var settings = $.extend({
          nid: '',
          
      }, options );      
      
      var spath = 'cmwn_games/object';
      
      $.ajax(
        {
         url: cmwn_games_url + spath + '?nid=' + settings.nid,
         dataType: "json",
         success:function(data){
          callback(data);
         }
        }
      );  
    };
    
    //Post new action item step to platform.
    $.fn.cmwn_games_logStep = function(options, callback) {
      var settings = $.extend({
          data: {},
      }, options );      
      
      var spath = 'cmwn_games/post';
      
      $.ajax(
        {
         url: cmwn_games_url + spath + '?nid=' + settings.nid,
         method:'GET',
         dataType: "json",
         data:settings.data,
         success:function(data){
          callback(data);
         }
        }
      );  
    };
   
    
    //get current step
    $.fn.cmwn_games_getCurrentStep = function(options, callback) {
      var settings = $.extend({
          data: {},
      }, options );      
      
      var spath = 'cmwn_games/current_step';
      
      $.ajax(
        {
         url: cmwn_games_url + spath + '?flip_nid=' + settings.flip_nid,
         method:'GET',
         dataType: "json",
         data:settings.data,
         success:function(data){
          callback(data);
         }
        }
      );  
    };    
    
    
    //get all steps
    $.fn.cmwn_games_getAllSteps = function(options, callback) {
      var settings = $.extend({
          data: {},
      }, options );      
      
      var spath = 'cmwn_games/flip';
      
      $.ajax(
        {
         url: cmwn_games_url + spath + '?flip_nid=' + settings.flip_nid,
         method:'GET',
         dataType: "json",
         data:settings.data,
         success:function(data){
          callback(data);
         }
        }
      );  
    };        
    //i.e.
    //$.fn.cmwn_games_getAllSteps({flip_nid:15441});

    //this function should be called to close the iframe/modal/whatever after the game is done.
    $.fn.cmwn_games_close = function(options) {
      window.location.href='/user';
    };
    //i.e. $.fn.cmwn_games_close();

}( jQuery ));

function completeFlip(flip_nid) { 
  $.fn.cmwn_games_getCurrentStep({flip_nid:flip_nid}, function(current_step) {
      
    if(current_step == 'completed_flip') {
      alert('You have already completed tihs flip!');
    } else {
        $.fn.cmwn_games_logStep({nid:current_step}, function(return_data) {
          alert('Good Job! You have earned a fip');
      });
    }
  });
}