#pragma once

#define DROP(obj) _Generic((obj), _TD(_impl_drop_))(&(obj))
