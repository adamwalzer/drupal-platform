(function ( $ ) {
    //change this for env.
    var cmwn_oauth_service_url = 'http://local.cmwn.com:8888/';
    
    //GET OAUTH TOKEN
    $.fn.cmwn_oauth_token = function(options) {

      var settings = $.extend({
          // These are the defaults.
          oauth_consumer_key: '',
          
      }, options );      
      
      var spath = 'services/authentication/application';
      var return_data;
      
      $.ajax(
        {
         async: false,
         url: cmwn_oauth_service_url + spath + '?oauth_consumer_key=' + settings.oauth_consumer_key,
         dataType: "json",
         success:function(data){
          return_data = data;
         }
        }
      );  
      return return_data;
    };
    
    //call like this but w/ your own real consumer key:
    /*var token = $.fn.cmwn_oauth_token({
      oauth_consumer_key: '',
    });
    console.log(token);*/
    
   
    //GET WEBFORM (action item step) object from drupal platform.
    //(use this to know what to post when you use the next function to post an action item step to the drupal platform)
    $.fn.cmwn_oauth_wf_object = function(options) {
      var settings = $.extend({
          // These are the defaults.
          oauth_consumer_key: '',
          oauth_token: '',
          webform_nid: '',
          
      }, options );      
      
      var spath = 'services/get_action_webform_object';
      var return_data;
      
      $.ajax(
        {
         async: false,
         url: cmwn_oauth_service_url + spath + '?oauth_consumer_key=' + settings.oauth_consumer_key + '&oauth_token=' + settings.oauth_token + '&webform_nid=' + settings.webform_nid,
         dataType: "json",
         success:function(data){
          return_data = data;
         }
        }
      );  
      return return_data;
    };
    
    //call like this but w/ your own real consumer key:
    /*var flip = $.fn.cmwn_oauth_wf_object({
      oauth_consumer_key: '7xicHsytf8k3FPRn6N9dU4wJRLfLphEW',
      oauth_token: $.fn.cmwn_oauth_token({oauth_consumer_key: '7xicHsytf8k3FPRn6N9dU4wJRLfLphEW'}).oauth_token,
      webform_nid: '12498',
    });
    console.log(flip);*/
    
    //Post new action item step to platform.
    //(Use this to log that a user has completed a step of an action item. Be sure to get the webform object using above function first so you know if there are 
    //any fields you need to submit
    $.fn.cmwn_oauth_post_webform = function(options) {
      var settings = $.extend({
          // These are the defaults.
          oauth_consumer_key: '',
          oauth_token: '',
          data: {},
      }, options );      
      
      var spath = 'services/post/action';
      var return_data;
      
      $.ajax(
        {
         async: false,
         url: cmwn_oauth_service_url + spath + '?oauth_consumer_key=' + settings.oauth_consumer_key + '&oauth_token=' + settings.oauth_token,
         method:'POST',
         dataType: "json",
         data:settings.data,
         success:function(data){
           console.log(settings.data);
          return_data = data;
         }
        }
      );  
      return return_data;
    };
    
    //call like this but w/ your own real consumer key:
    /*var flip = $.fn.cmwn_oauth_post_webform({
      oauth_consumer_key: '7xicHsytf8k3FPRn6N9dU4wJRLfLphEW',
      oauth_token: $.fn.cmwn_oauth_token({oauth_consumer_key: '7xicHsytf8k3FPRn6N9dU4wJRLfLphEW'}).oauth_token,
      data:{
        first_name: 'Luke Meier',
        nid: '12498',//this is the nid of the webform action step
        uid: '4980',        
        flip_nid:'12499',//this is the nid of the flip node which contains references to all action item steps
      }
    });
    console.log(flip);*/
    //in this example
    //flip action item step submission will be viewable here http://local.cmwn.com:8888/node/12498/webform-results

    
 
}( jQuery ));