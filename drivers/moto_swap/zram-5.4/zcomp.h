/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2014 Sergey Senozhatsky.
 */

#ifndef _ZCOMP_H_
#define _ZCOMP_H_

struct zcomp_strm {
	/* compression/decompression buffer */
	void *buffer;
	struct crypto_comp *tfm;
};

/* dynamic per-device compression frontend */
struct zcomp {
	struct zcomp_strm * __percpu *stream;
	const char *name;
	struct hlist_node node;
};

int moto_zcomp_cpu_up_prepare(unsigned int cpu, struct hlist_node *node);
int moto_zcomp_cpu_dead(unsigned int cpu, struct hlist_node *node);
ssize_t moto_zcomp_available_show(const char *comp, char *buf);
bool moto_zcomp_available_algorithm(const char *comp);

struct zcomp *moto_zcomp_create(const char *comp);
void moto_zcomp_destroy(struct zcomp *comp);

struct zcomp_strm *moto_zcomp_stream_get(struct zcomp *comp);
void moto_zcomp_stream_put(struct zcomp *comp);

int moto_zcomp_compress(struct zcomp_strm *zstrm,
		const void *src, unsigned int *dst_len);

int moto_zcomp_decompress(struct zcomp_strm *zstrm,
		const void *src, unsigned int src_len, void *dst);

bool zcomp_set_max_streams(struct zcomp *comp, int num_strm);
#endif /* _ZCOMP_H_ */
