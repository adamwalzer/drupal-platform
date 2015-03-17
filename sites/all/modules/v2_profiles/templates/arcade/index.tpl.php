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
    <iframe width=624 style="height:1500px;border: 0;" scrolling="no" border=0 src="http://arcade.changemyworldnow.com"></iframe>
  		  
  	</div>
  	<?php  }?>
  </div>
 </div>
