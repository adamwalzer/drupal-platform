<?php /* 1.4 */ ?>

<div class="block links index">

	<div class="content">

		<div class="section">
			<ul>
				<?php foreach ($data->items as $index => $item) { ?>
					<li<?php echo($item->active||$item->title=='Add a Child'?' class="'.($item->active?'active':'').($item->title=='Add a Child'?' add-a-child':'').'"' : ''); ?>>
					<a href="<?php print $item->href; ?>"><?php print $item->title; ?></a>
					</li>
				<?php } ?>
			</ul>
		</div>

	</div>

</div>

<div class="block links modal interests" id="links-interests" style="display:none;">

	<div class="section">
		<ul>
			<?php foreach ($data->interests as $item) { ?>
				<li class="<?php print $item->class; ?>"><a href="<?php print $item->href; ?>"><?php print $item->title; ?></a></li>
			<?php } ?>
		</ul>
	</div>

</div>