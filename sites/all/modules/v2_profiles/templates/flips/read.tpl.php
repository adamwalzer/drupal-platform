<?php
if($data->user->user_type != 'child') {
	header('Location: /user/');
	exit();
}
?> 
<div class="block flips action <?php print $data->node->color; ?>">
	
		<iframe class="gameframe" src="/<?php print $data->node->field_game_filepath[0]['value'];?>" scrolling="no" frameborder="0" width="624" height="624"></iframe>	
	
</div>