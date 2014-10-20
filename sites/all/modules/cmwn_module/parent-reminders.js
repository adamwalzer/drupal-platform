jQuery(function($){
  $('#sendReminders').click(function(e){
    e.preventDefault();
    var ids = [];
    $('input.user:checked').each(function(){
      ids.push($(this).attr('id').substring(5));
    });
    //console.log(ids.join(','));
    document.location = Drupal.settings.basePath+'admin/user/parent-reminders/confirm?include='+ids.join(',');
  });
})