<?php

/**
 * @file
 * Node storage adapter for Recycle Bin.
 */

/**
 * Node controller that turns opted-in deletes into soft deletes.
 */
class RecycleBinNodeStorageController extends NodeStorageController {
  use RecycleBinStorageAdapterTrait;
}

