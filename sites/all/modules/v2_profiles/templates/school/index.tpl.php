<?php /* 1.4 */ ?>

<div class="block school shadow index whiteboard">

	<div class="header">

		<div class="section">
			<?php if ($data->school): ?>
			<h2><?php print $data->school->title; ?></h2>
		<?php endif;?>
		</div>
  </div>
  
	<div class="content p">

		<div class="section">
			<?php if ($data->school) { ?>
				<div class="my-school-image"><?php print theme('image', 'sites/all/themes/cmwn/assets/img/school-icon.png'); ?></div>
				
				
        <div class="school-left">
          <div class="school-location"><label>Location</label><br><p><?php print $data->school->field_school_city[0]['value'];?>, <?php print $data->school->field_school_state[0]['value'];?></p></div>
    			<div class="school-district">
      			<label>District</label><br>
      			<p><?php $district = node_load($data->school->field_district[0]['nid']);
        			print $district->field_office_address[0]['value'];
        		?></p>
      			
    			</div>

    		</div>
    		
    		<div class="school-right">
          <div class="school-students-count">
            <?php 
              //todo: optimize this to cache this info
            $students =  db_result(db_query('select count(*) as studentcount from {content_field_school} cfs join {node} n on n.nid = cfs.nid and n.vid = cfs.vid and n.type="child_profile" where cfs.field_school_nid = %d',$data->school->nid));
            ?>
            <label>Students</label><br><p><?php print $students;?></p>
          </div>      		
    			<div class="school-teachers-count">
      			<label>Teachers</label><br>
      			<p><?php
        			//todo: optimize this
        			$teachers = db_result(db_query('select count(*) as teachercount from {content_field_school} cfs join {node} n on n.nid = cfs.nid and n.vid = cfs.vid and n.type="teacher_profile" where cfs.field_school_nid = %d',$data->school->nid));			
              print $teachers;
      			?></p>
    			</div>
    		</div>  				
							
			<?php } else { ?>
			<div class="empty">
				There are no schools.
			</div>
			<?php } ?>
		</div>

	</div>

</div>

<div class="block shadow index whiteboard">
  
  <div class="header">
    <div class="section">
          <h2>Whiteboard</h2>
    </div>
  </div>
  <div class="content school-whiteboard">
    <div id="whiteboard-tab">
    <?php 
      print theme('v2_profiles_whiteboard_tab',$data);
    ?>
    </div>
  </div>
  
</div>