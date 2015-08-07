<?php /* 1.4 */ ?>

<div class="block links index">

	<div class="content">

		<div class="section">
			<?php

				print theme('item_list',$data->items,null,'ul',array('class' => 'profile-links'));

			?>
		</div>

	</div>

</div>


<?php if(false):?>
<div class="block links modal interests" id="links-interests">

	<div class="section">
		<ul>
			<?php foreach ($data->interests as $item) { ?>
				<li class="<?php print $item->class; ?>"><a href="<?php print $item->href; ?>"><?php print $item->title; ?></a></li>
			<?php } ?>
		</ul>
	</div>

</div>
<?php endif;?>