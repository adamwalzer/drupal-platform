<div id="overlay-reminder">
  <div class="contentWrap">
    <p style="font-size:26px;color:#54c2f2;float:left;width:310px;">Congratulations! Your registration has been confirmed.</p>
    <p style="font-size:14px;color:#6d6d6d;float:right;width:210px;">Please don't forget to visit your child's profile page to set PERMISSIONS. Your children will not have the ability to interact on our website without your permission.
    <br /><br />Questions? Just email us: <a href="mailto:askus@changemyworldnow.com"></a>askus@changemyworldnow.com</a></p>
    <!-- <a class="close button grey"><span>Remind me Later</span></a> -->
    <a class="close button purple" style="float:right;" id="overlay-reminder-confirm"><span>Let's get started!</span></a>
  </div>
</div>
<script type="text/javascript">
jQuery(function(){
  $('#overlay-reminder').overlay({
    mask: '#ccc',
    load: true,
    closeOnClick: false
  });
  $('#overlay-reminder-confirm').click(function(){
    //document.location = '<?php print url('user'); ?>';
  });
});
</script>