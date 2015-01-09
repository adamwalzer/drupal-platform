<?php
  
global $cmwn_feed_menu_items;
$cmwn_feed_menu_items['cmwn_feed/friend'] = array(
  'page callback' => 'cmwn_friend_feed',
  'access arguments' => array('access content'),
  'type' => MENU_CALLBACK,
);
  
function cmwn_feed_friend_queries_list(){
  $feed_queries = array(
    'friend request',
    'completes flip milestone',
    'signs up flip',
    'completes flip',
    'post on own whiteboard',
    'post on other whiteboard', 
    'joins special edition flip', 
    'reply to own post', 
    'reply to other post', 
  );  
  return $feed_queries;
}

function cmwn_feed_friend_query_weights(){
  
  $result = db_query("SELECT query_name, weight FROM {cmwn_feed_weight} cfw");
  
  $weights = array();
  
  while ($row = db_fetch_object($result)) {
    $weights[$row->query_name] = (float)$row->weight;
  }     
  
  return $weights;

}

function cmwn_feed_get_timeago($field){
  return "CASE 
            WHEN FROM_UNIXTIME(" . $field . ") between date_sub(now(), INTERVAL 60 minute) and now() THEN concat(minute(TIMEDIFF(now(), FROM_UNIXTIME(" . $field . "))), ' minute(s) ago')
            WHEN datediff(now(), FROM_UNIXTIME(" . $field . ")) = 1 THEN 'Yesterday'
            WHEN FROM_UNIXTIME(" . $field . ") between date_sub(now(), INTERVAL 48 hour) and now() THEN concat(hour(TIMEDIFF(NOW(), FROM_UNIXTIME(" . $field . "))), ' hour(s) ago')
          ELSE date_format(FROM_UNIXTIME(" . $field . "), '%a, %m/%%d/%y %h:%%i%p')
          END      	as time_ago
          ";
}  
function cmwn_friend_feed($uid = 0, $page = 0) {//ganked/modified from feed.inc in v2 profile
    
		$items = array();
    global $user;
    global $feed_queries;
    $weights = cmwn_feed_friend_query_weights();
		$friend_feed_user = user_load($uid);

		if (!$friend_feed_user || $user->uid != $uid){
  		print '';
  		exit();
		} 		

		//Friend feed - find all this person's friends first!
		$query = "SELECT requester_id as friend_uid FROM {user_relationships} WHERE requestee_id = %d and approved =1 order by updated_at desc";
		
		$results = db_query($query, $uid);

    $friends = array();
    
		while ($result = db_fetch_object($results)) {
      $friends[] = $result->friend_uid;
		}
		
		//add our uid!
		$friends[] = $uid;
    
    $friend_uid_placeholders = db_placeholders($friends);
		
    $feed_queries['friend request'] = array(
      	'query' => "(SELECT CONCAT('<a href=\"/user/', user_a.uid,'\">',user_a.name,'</a> has become friends with <a href=\"/user/',user_b.uid, '\">', user_b.name, '</a>') as excerpt, user_a.uid as uid, updated_at as stamp, (updated_at*".$weights['friend request'].") as s,
        
        ".cmwn_feed_get_timeago('updated_at')."
      	
 FROM {user_relationships} ur join {users} user_a on ur.requester_id = user_a.uid join {users} user_b on user_b.uid = ur.requestee_id WHERE requester_id in($friend_uid_placeholders) and approved = 1) UNION ALL ",
      );
      
      $feed_queries['completes flip milestone'] = array(
      	'query' => "(SELECT CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has completed the action item milestone \"<em>', n.title ,'</em>.\"') as excerpt, ws.uid as uid, submitted as stamp, (submitted*".$weights['completes flip milestone'].") as s,
      
        ".cmwn_feed_get_timeago('submitted')."
        
        FROM {webform_submissions} ws JOIN {node} n on n.nid = ws.nid join {users} u on u.uid = ws.uid and n.type='action' WHERE ws.uid in($friend_uid_placeholders)) UNION ALL ",
      );
      
      $feed_queries['signs up flip'] = array(
      	'query' => "(select CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has begun the action item \"<em>', nf.title ,'</em>.\"') as excerpt, ws.uid as uid, ws.submitted as stamp, (ws.submitted*".$weights['signs up flip'].") as s,
      
          ".cmwn_feed_get_timeago('ws.submitted')."
          
         from {webform_submissions} ws join node na on ws.nid = na.nid join {content_field_actions} cfa on cfa.field_actions_nid = na.nid join {node} nf on nf.nid = cfa.nid join {users} u on u.uid = ws.uid where ws.uid in($friend_uid_placeholders) and cfa.delta = (select min(delta) from {content_field_actions} cfai where cfai.nid = nf.nid))  UNION ALL ",
      );

      $feed_queries['joins special edition flip'] = array(
      	'query' => "(select CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has begun has joined special edition flip \"<em>', nf.title ,'</em>.\"') as excerpt, ws.uid as uid, ws.submitted as stamp, (ws.submitted*".$weights['joins special edition flip'].") as s,
      
        ".cmwn_feed_get_timeago('ws.submitted')."

         from {webform_submissions} ws join node na on ws.nid = na.nid join {content_field_actions} cfa on cfa.field_actions_nid = na.nid join {node} nf on nf.nid = cfa.nid join {users} u on u.uid = ws.uid join {content_field_special_edition} cfse on cfse.nid = nf.nid and cfse.field_special_edition_value='Yes' where ws.uid in($friend_uid_placeholders) and cfa.delta = (select min(delta) from {content_field_actions} cfai where cfai.nid = nf.nid))  UNION ALL ",
      );

      
      $feed_queries['completes flip'] = array(
      	'query' => "(select CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has completed the action item \"<em>', nf.title ,'</em>.\"') as excerpt, ws.uid as uid, ws.submitted as stamp, (ws.submitted*".$weights['completes flip'].") as s,
      	
        ".cmwn_feed_get_timeago('ws.submitted')."
        
      	 from {webform_submissions} ws join node na on ws.nid = na.nid join {content_field_actions} cfa on cfa.field_actions_nid = na.nid join {node} nf on nf.nid = cfa.nid join {users} u on ws.uid = u.uid where ws.uid in($friend_uid_placeholders) and cfa.delta = (select max(delta) from {content_field_actions} cfai where cfai.nid = nf.nid)) UNION ALL ",
      );  

      $feed_queries['reply to own post'] = array(
      	'query' => "(select CONCAT('<a href=\"/user/', c.uid,'\">', u.name, '</a> has commented on their own post.') as excerpt, 
      	c.uid as uid,
      	  timestamp as stamp, 
      	  (timestamp*".$weights['reply to own post'].") as s,
      	
        ".cmwn_feed_get_timeago('timestamp')."

      	 from {comments} c join {node} n on n.type = 'whiteboard' and n.nid = c.nid join 
      	 
      	  {content_type_whiteboard} ctw on ctw.nid = n.nid and ctw.field_user_reference_uid = c.uid
      	 
          JOIN {users} u on u.uid = c.uid
      	 
      	  where c.uid in ($friend_uid_placeholders) and c.status = 1) UNION ALL ",
      );
      
      
      $feed_queries['reply to other post'] = array(
      	'query' => "(select CONCAT('<a href=\"/user/', c.uid,'\">', u.name, '</a> has commented on <a href=\"/user/', u2.uid,'\">' , u2.name , '\\'s</a> post.') as excerpt, 
      	c.uid as uid,
      	  timestamp as stamp, 
      	  (timestamp*".$weights['reply to other post'].") as s,
      	
        ".cmwn_feed_get_timeago('timestamp')."

      	 from {comments} c join {node} n on n.type = 'whiteboard' and n.nid = c.nid join 
      	 
      	  {content_type_whiteboard} ctw on ctw.nid = n.nid and ctw.field_user_reference_uid <> c.uid
      	 
          JOIN {users} u on u.uid = c.uid
          
          JOIN {users} u2 on u2.uid = n.uid
      	 
      	  where c.uid in ($friend_uid_placeholders) and c.status =1) UNION ALL ",
      );
      

      $feed_queries['post on own whiteboard'] = array(//carefully note - the field_user_reference on this websites determines who actually made the post. node.uid is not the actual author but whose whiteboard the post appears on.
      	'query' => "(select CONCAT('<a href=\"/user/', n.uid,'\">', u.name, '</a> has posted on their own whiteboard.') as excerpt, 
      	n.uid as uid,
      	  n.created as stamp, 
      	  (n.created*".$weights['post on own whiteboard'].") as s,
      	
        ".cmwn_feed_get_timeago('n.created')."

      	 from {node} n join {users} u on u.uid = n.uid join {content_type_whiteboard} ctw on ctw.nid = n.nid and ctw.field_user_reference_uid = n.uid where n.type='whiteboard' and
      	 ctw.field_user_reference_uid in ($friend_uid_placeholders) and n.status = 1) UNION ALL ",
      );		


      $feed_queries['post on other whiteboard'] = array(
      	'query' => "(select CONCAT('<a href=\"/user/', u2.uid, '\">', u2.name, '</a> has posted on <a href=\"/user/', u.uid,'\">', u.name ,'s</a> whiteboard.') as excerpt, 
      	n.uid as uid,
      	  n.created as stamp, 
      	  (n.created*".$weights['post on other whiteboard'].") as s,
      	
        ".cmwn_feed_get_timeago('n.created')."

      	 from {node} n join {users} u on u.uid = n.uid join {content_type_whiteboard} ctw on ctw.nid = n.nid join {users} u2 on u2.uid = ctw.field_user_reference_uid where ctw.field_user_reference_uid <> n.uid and n.type='whiteboard' and n.status = 1 and ctw.field_user_reference_uid in ($friend_uid_placeholders)) ",
      );
      
    
		$args = array();
    foreach($feed_queries as $type => $query){
      $query_union .= $query['query'];
      $args = array_merge($args,$friends);
    }

    $query_union = $query_union . '  order by s desc';

    $count_query = "SELECT COUNT(*) FROM (" . $query_union . ") AS count_query";
    

    
    $feed_items = pager_query($query_union, 13, 0, $count_query, $args);//careful here, $args must work for count query and main query or this wont work.

    while($f = db_fetch_object($feed_items)){
      $item = new stdClass();
  		$item->excerpt = $f->excerpt;
      $item->src = v2_profiles_avatars_query($f->uid);
  		$item->stamp = $f->stamp;
  		$item->time_ago = $f->time_ago;
  		$items[] = $item;
    }
		?>
		
    <?php foreach ($items as $item) { ?>
      	<div class="item">
      		<span class="image">
      			<img height="42" src="<?php print $item->src; ?>" width="42" />
      		</span>
      		<?php
      			$_excerpt = $item->excerpt  . ' <em class="feed-time">' .  $item->time_ago . '</em>';
      			$_excerpt = str_replace('/user/'.$user->uid, '/user', $_excerpt);
      			$_excerpt = preg_replace('/("\/user\/)([0-9]+)(")/i', '"/user/'.$user->uid.'/friends/$2/"', $_excerpt);
      		?>
      		<span class="message">
      			<?php print $_excerpt; ?>
      		</span>
      	</div>
    <?php } ?>		
    <?php
      print theme('pager', NULL, 10, 0);
      exit;
}