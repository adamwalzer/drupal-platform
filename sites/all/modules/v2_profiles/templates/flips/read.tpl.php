<?php /* 1.4 */ ?>
<?php
if($data->user->user_type=='parent') {
	header('Location: /user/');
	exit();
}
?>

<?php if ($data->node->completed == 1) { ?>
	<div class="message-modal-underlay" id="message-modal-underlay">
		<div class="message-modal">
			<a href="#" class="close-message-modal x-close"></a>
			<div class="heading">Thank you for<br />Changing the World!</div>
			<a href="/user/" class="button"><span>Return to Profile</span></a>
		</div> <!-- /.message-modal -->
	</div> <!-- /.message-modal-underlay -->
	<script type="text/javascript">
		$("#v2").append($("#message-modal-underlay"));
		var theModal = $("#message-modal-underlay .message-modal");
		$(theModal).css({'margin-top': '-'+($(theModal).height()/2)+"px"});
		$(".close-message-modal").click(function() {
			$(".message-modal-underlay").fadeOut("slow",function() {
				$(this).remove();
			});
		});
	</script>
<?php } ?>

<div class="block shadow flips action <?php print $data->node->color; ?>">

	<div class="header">

		<div class="section">
			<h2>
				<img src="/<?php print $data->node->logo; ?>" />
				<?php print $data->node->title; ?>
			</h2>
			<p>Change My World Now is proud to partner with <a href="<?php print $data->node->partner->href; ?>"><?php print $data->node->partner->title; ?></a> to bring you this Action Item.</p>
		</div>

	</div>

	<div class="content">

		<div class="section step">
			<div class="cms">

				<?php
					$classes = array(2=>'the-story',3=>'your-role',4=>'think-about-it',5=>'take-action');
					foreach ($classes as $key => $value) {
						$title = $data->node->{'field_instruction_'.$key.'_title'}[0]['value'];
						$instruction = $data->node->{'field_instruction_'.$key.''}[0]['value'];
						$more = $data->node->{'field_instruction_'.$key.'_more'}[0]['value'];
						if (!empty($instruction)) {
							print '<h3 class="'.$value.'">'.$title.'</h3>';
							print '<p>'.$instruction.'</p>';
							if (!empty($more)) {
								print '<div class="collapsed" style="display:none;">'.$more.'</div>';
								print '<p class="more"><a class="button" href="#">Read More</a></p>';
							}
						}
					}
				?>
        <?php
          $already_started = false;
          foreach ($data->node->items as $key => $item){
            if($item->completed == 1){
              $already_started = true;
            }
          }
        ?>
        <?php if(!$already_started):?>
  				<p class="start"><a class="button" href="#">I'm Ready To Start</a></p>
				<?php else:?>
	  			<p class="start started"><a class="button" href="#">Completed</a></p>
				<?php endif;?>

			</div>
		</div>

		<?php foreach ($data->node->items as $key => $item) { ?>
			<div class="section step n<?php print ($key+1); ?><?php print ($item->disabled == 1 || ($item->completed == 0 && $item->disabled == 0 && $key == 0))? ' disabled' : ''; ?>">
				<div class="number">
					<?php print ($key+1); ?>
				</div>
				<div class="cms">
					<h3><?php print $item->title; ?></h3>
					<?php if ($item->completed == 0) { ?>
						<?php
							print '<iframe border="0" class="flip-iframe" scrolling="no" src="' . $item->node->field_action_external_url[0]['url'] . '?username=' . $data->user->name . '&avatar=' . $data->user->avatar . '"></iframe>';
							print node_view($item->node);
						?>
					<?php } else { ?>
						<?php
							if ($item->node->webform['components']) {
								foreach ($item->node->webform['components'] as $component) {
									if ($component['type'] == 'markup') {
										print '<p>' . $component['value'] . '</p>';
									}
								}
							}
						?>
						<p class="completed">Completed.</p>
					<?php } ?>
				</div>
				<?php if (($key+1) < sizeof($data->node->items)) { ?>
					<div class="separator">
						separator
					</div>
				<?php } ?>
			</div>
		<?php } ?>

		<?php if ($data->node->completed == 1) { ?>
			<div class="section step">
				<div class="cms">
					<h3>What Now?</h3>
					<?php $instruction = $data->node->field_instruction_6[0]['value']; ?>
					<?php print $instruction; ?>
				</div>
			</div>
		<?php } ?>

	</div>

</div>

<?php if ($data->node->new == 1) { ?>
	<div class="block modal" id="safety-tips" style="display:none;">
		<div class="section title">
			<h1>Safety Tips</h1>
		</div>
		<div class="section cms">
			<?php $instruction = $data->node->field_instruction_1[0]['value']; ?>
			<?php print $instruction; ?>
		</div>
		<div class="section buttons">
			<a href="#" class="button primary">Let's Do This</a>
		</div>
	</div>
<?php } ?>
