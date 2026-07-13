<?php

/**
 * @file
 * Managed-file storage adapter for Recycle Bin.
 */

/**
 * File controller that protects opted-in permanent managed files.
 */
class RecycleBinFileStorageController extends FileStorageController {
  use RecycleBinStorageAdapterTrait;
}

