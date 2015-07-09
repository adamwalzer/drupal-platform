<?php

class ChildUser extends GenericUser {
  
  protected $_childProfile;
  protected static $tokens = array();
  
  /**
   * 
   * Enter description here ...
   * @param unknown_type $obj
   * @return ChildUser
   */
  public static function castAs($obj) {
    if ($obj instanceof ChildUser) {
      return $obj;
    }
    try {
      $obj = new ChildUser($obj);
      return $obj;
    } catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'error');
      return false;
    }
  }
  
  public function getChildProfile() {
    return $this->_childProfile;
  }
  
  public static function canHydrate($obj) {
    return isset($obj->roles) && is_array($obj->roles) && in_array(get_role_from_rid(variable_get('cmwn_module_child_role','')), $obj->roles);
  }
  
  public function __construct($obj) {
    if (!self::canHydrate($obj)) {
      throw new Exception('Unable to cast object as ChildUser.');
    }
    parent::__construct($obj);
    $this->_childProfile = content_profile_load('child_profile', $this->uid);
  }
  
  public function getParentalConsentToken() {
    if (isset(self::$tokens[$this->uid])) {
      return self::$tokens[$this->uid];
    }
    $token = db_fetch_array(db_query("SELECT * FROM {cmwn_parental_consent_token} WHERE cuid = '%s'", $this->uid));
    if ($token) {
      self::$tokens[$this->uid] = $token;
      return $token;
    }
    for ($i = 0; $i < 24; $i++) {
      $token .= chr(mt_rand(0,1) == 0 ? mt_rand(ord('A'), ord('Z')) : mt_rand(ord('0'), ord('9')));
    }
    $row = array(
      'cuid' => $this->uid,
      'puid' => 0,
      'puip' => 0,
      'token' => $token,
      'created' => time()
    );
    if (drupal_write_record('cmwn_parental_consent_token', $row)) {
      self::$tokens[$this->uid] = $row;
      return $row;
    }
    return false;
  }
  
  public function getSchool() {
    $sql = <<<EOSQL
SELECT
	n2.nid
FROM {node} n
INNER JOIN {content_field_school} cfs ON cfs.vid = n.vid
INNER JOIN {node} n2 ON cfs.field_school_nid = n2.nid

WHERE n.uid = %d limit 1
EOSQL;
    $nid = db_result(db_query($sql, $this->uid));
    return node_load($nid);
  }
  
  public function getFriends() {
    $sql = <<<EOSQL
SELECT DISTINCT u.uid, u.name FROM {user_relationships} ur
INNER JOIN {users} u ON u.uid IN (ur.requester_id, ur.requestee_id)
WHERE %d IN (ur.requester_id, ur.requestee_id)
AND ur.approved = 1
AND ur.rtid = 4
AND u.uid != %d
EOSQL;
    $friends = array();
    $result = db_query($sql, $this->uid, $this->uid);
    while ($row = db_fetch_object($result)) {
      $friends[] = $row;
    }
    return $friends;
  }
  
  public function isFriendsWith($child) {
    $rel = user_relationships_load(array('between' => array($this->uid, $child->uid)));
    $rel = array_pop($rel);
    return $rel && $rel->approved;
  }
  
  public function isChildOf($parent) {
    if (!ParentUser::canHydrate($parent)) {
      return false;
    }
    $children = ParentUser::castAs($parent)->getChildren();
    $found = false;
    foreach ($children as $child) {
      if ($child->uid == $this->uid) {
        $found = true;
      }
    }
    return $found;
  }
  
  public function getInterests($exclude_non_membership = false) {
    if ($exclude_non_membership) {
      $sql = <<<EOSQL
SELECT
n.nid,
n.title,
f1.filepath AS small_image_active,
f2.filepath AS small_image_inactive,
f3.filepath AS large_image_active,
f4.filepath AS large_image_inactive,
1 AS is_member
FROM {node} n
INNER JOIN {og_uid} ou ON ou.nid = n.nid
INNER JOIN {content_type_interest} cti ON cti.vid = n.vid
INNER JOIN {files} f1 ON f1.fid = cti.field_interest_small_image_a_fid
INNER JOIN {files} f2 ON f2.fid = cti.field_interest_small_image_i_fid
INNER JOIN {files} f3 ON f3.fid = cti.field_interest_large_image_a_fid
INNER JOIN {files} f4 ON f4.fid = cti.field_interest_large_image_i_fid
WHERE n.type = 'interest'
AND ou.uid = %d
EOSQL;
    } else {
      $sql = <<<EOSQL
SELECT
n.nid,
n.title,
f1.filepath AS small_image_active,
f2.filepath AS small_image_inactive,
f3.filepath AS large_image_active,
f4.filepath AS large_image_inactive,
(SELECT 1 FROM {og_uid} ou WHERE ou.uid = %d AND ou.nid = n.nid) AS is_member
FROM {node} n
INNER JOIN {content_type_interest} cti ON cti.vid = n.vid
INNER JOIN {files} f1 ON f1.fid = cti.field_interest_small_image_a_fid
INNER JOIN {files} f2 ON f2.fid = cti.field_interest_small_image_i_fid
INNER JOIN {files} f3 ON f3.fid = cti.field_interest_large_image_a_fid
INNER JOIN {files} f4 ON f4.fid = cti.field_interest_large_image_i_fid
WHERE n.type = 'interest'
EOSQL;
    }
    $interests = array();
    $result = db_query($sql, $this->uid);
    while ($row = db_fetch_object($result)) {
      $interests[] = $row;
    }
    return $interests;
  }
  
  public function hasCompletedInterestSurvey() {
    $sql = "SELECT sid FROM {webform_submissions} WHERE uid = %d AND nid = %d";
    return db_result(db_query($sql, $this->uid, variable_get('cmwn_survey_interest_survey_nid', ''))) ? true : false;
  }
  
}