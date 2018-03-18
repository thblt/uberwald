ubw_contname* ubw_contname_init(ubw_contname *s, const int capacity, ubw_conttype *dptr) {
  s->d = (NULL != dptr) ? dptr : malloc(capacity*sizeof(ubw_conttype));
  s->c = capacity;
  s->h = 0;

    return s;
}

ubw_conttype * ubw_contname_peek(const ubw_contname *s) {
  if (0 < s->h) {
    return & s->d[(s->h)-1];
  } else {
    return NULL;
  }
}

ubw_conttype * ubw_contname_fpeek(const ubw_contname *s) {
  return & s->d[(s->h)-1];
}

ubw_conttype * ubw_contname_pop(ubw_contname *s) {
  if (0 < s->h) {
    return & s->d[--(s->h)];
  } else {
    return NULL;
  }
}

ubw_conttype * ubw_contname_fpop(ubw_contname *s) {
  return & s->d[--(s->h)];
}

ubw_conttype * ubw_contname_push(ubw_contname *s, ubw_conttype* o) {
  if (s->h < s->c) {
    s->d[(s->h)++] = *o;
    return &s->d[s->h];
  } else {
    return NULL;
  }
}

ubw_conttype * ubw_contname_cpush(ubw_contname *s, ubw_conttype o) {
  if (s->h < s->c) {
    s->d[s->h++] = o;
    return &s->d[s->h];
  } else {
    return NULL;
  }
}

ubw_conttype * ubw_contname_fpush(ubw_contname *s, ubw_conttype* o) {
  s->d[s->h++] = *o;
  return &s->d[s->h];
}

ubw_conttype * ubw_contname_fcpush(ubw_contname *s, ubw_conttype o) {
  s->d[s->h++] = o;
  return &s->d[s->h];
}
