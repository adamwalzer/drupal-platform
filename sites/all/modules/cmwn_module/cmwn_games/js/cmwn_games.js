(function ( $ ) {

    var cmwn_games_url = location.protocol + "//" + location.host + "/";
    
    //GET WEBFORM (action item step) object from drupal platform.
    $.fn.cmwn_games_object = function(options) {
      var settings = $.extend({
          nid: '',
          
      }, options );      
      
      var spath = 'cmwn_games/object';
      var return_data;
      
      $.ajax(
        {
         async: false,
         url: cmwn_games_url + spath + '?nid=' + settings.nid,
         dataType: "json",
         success:function(data){
          return_data = data;
         }
        }
      );  
      return return_data;
    };

    
    //Post new action item step to platform.
    $.fn.cmwn_games_logStep = function(options) {
      var settings = $.extend({
          data: {},
      }, options );      
      
      var spath = 'cmwn_games/post';
      var return_data;
      
      $.ajax(
        {
         async: false,
         url: cmwn_games_url + spath + '?nid=' + settings.nid,
         method:'GET',
         dataType: "json",
         data:settings.data,
         success:function(data){
          return_data = data;
         }
        }
      );  
      return return_data;
    };
   
    
    //get current step
    $.fn.cmwn_games_getCurrentStep = function(options) {
      var settings = $.extend({
          data: {},
      }, options );      
      
      var spath = 'cmwn_games/current_step';
      var return_data;
      
      $.ajax(
        {
         async: false,
         url: cmwn_games_url + spath + '?flip_nid=' + settings.flip_nid,
         method:'GET',
         dataType: "json",
         data:settings.data,
         success:function(data){
          return_data = data;
         }
        }
      );  
      return return_data;
    };    
    
    
    //get all steps
    $.fn.cmwn_games_getAllSteps = function(options) {
      var settings = $.extend({
          data: {},
      }, options );      
      
      var spath = 'cmwn_games/flip';
      var return_data;
      
      $.ajax(
        {
         async: false,
         url: cmwn_games_url + spath + '?flip_nid=' + settings.flip_nid,
         method:'GET',
         dataType: "json",
         data:settings.data,
         success:function(data){
          return_data = data;
         }
        }
      );  
      return return_data;
    };        
    //i.e.
    //$.fn.cmwn_games_getAllSteps({flip_nid:15441});

    //this function should be called to close the iframe/modal/whatever after the game is done.
    $.fn.cmwn_games_close = function(options) {
      window.location.href='/user';
    };
    //i.e. $.fn.cmwn_games_close();

}( jQuery ));