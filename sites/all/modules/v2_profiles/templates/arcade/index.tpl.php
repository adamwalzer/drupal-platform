<?php /* 1.4 */ ?>

<div class="block shadow whiteboard arcade index">

  		<div class="header">
    		<div class="section">
          <a href="#whiteboard-tab"><h2>Arcade</h2></a>
    		</div>
  		</div>

  <div id="arcade-tab">
  	<?php if($user->user_type == 'child' || $user->user_type == 'parent' || $user->user_type == 'teacher') { ?>
  	<div class="items">
    <?php if (strpos($_SERVER['HTTP_USER_AGENT'], 'Chrome') !== false || strpos($_SERVER['HTTP_USER_AGENT'], 'CriOS') !== false):?>
      <div class="arcade-error">
        Hold on!
        This game is best experienced
        using Internet Explorer or Safari.
      </div>
    <?php else: ?>
      <iframe width=624 style="height:1500px;border: 0;" scrolling="no" border=0 src="http://arcade.changemyworldnow.com?uid=<?php print $user->uid; ?>"></iframe>
    <?php endif; ?>
    
  		  
  	</div>
  	<?php  }?>
  </div>
 </div>
